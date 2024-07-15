// SPDX-FileCopyrightText: 2000-2010 University College London, Alasdair Turner
// SPDX-FileCopyrightText: 2011-2012 Tasos Varoudis
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "salalib/shapemapgroupdata.h"

#include "genlib/p2dpoly.h"

#include <deque>
#include <string>

class ShapeMapGroupDataDX {

    ShapeMapGroupData m_mapGroupData;
    mutable std::optional<size_t> m_currentLayer;

  public:
    ShapeMapGroupDataDX(ShapeMapGroupData &&mapGroupData) : m_mapGroupData(mapGroupData) {
        m_currentLayer = std::nullopt;
    }
    ShapeMapGroupDataDX(const std::string &name = std::string()) : m_mapGroupData(name) {
        m_currentLayer = std::nullopt;
    }
    ShapeMapGroupDataDX(ShapeMapGroupDataDX &&other)
        : m_mapGroupData(other.m_mapGroupData), m_currentLayer(other.m_currentLayer) {}
    ShapeMapGroupDataDX &operator=(ShapeMapGroupDataDX &&other) {
        m_mapGroupData = other.m_mapGroupData;
        m_currentLayer = other.m_currentLayer;
        return *this;
    }
    ShapeMapGroupDataDX(const ShapeMapGroupDataDX &) = default;
    ShapeMapGroupDataDX &operator=(const ShapeMapGroupDataDX &) = default;

    void setName(const std::string &name) { m_mapGroupData.name = name; }
    const std::string &getName() const { return m_mapGroupData.name; }

    const QtRegion &getRegion() const { return m_mapGroupData.region; }
    void setRegion(QtRegion region) { m_mapGroupData.region = region; }

    const ShapeMapGroupData &getInternalData() const { return m_mapGroupData; }

    bool hasCurrentLayer() const { return m_currentLayer.has_value(); }
    int getCurrentLayer() const {
        return m_currentLayer.has_value() ? static_cast<int>(*m_currentLayer) : -1;
    }
    void invalidateCurrentLayer() const { m_currentLayer = std::nullopt; }
    void setCurrentLayer(int currentLayer) const { m_currentLayer = currentLayer; }

  public:
    bool read(std::istream &stream);
    bool write(std::ofstream &stream);
};