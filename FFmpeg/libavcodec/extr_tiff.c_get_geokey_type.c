#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  CONF ; 
 int /*<<< orphan*/  GEOG ; 
 int /*<<< orphan*/  PROJ ; 
 int /*<<< orphan*/  RET_GEOKEY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERT ; 
 int /*<<< orphan*/  conf ; 
 int /*<<< orphan*/  geog ; 
 int /*<<< orphan*/  proj ; 
 int /*<<< orphan*/  type ; 
 int /*<<< orphan*/  vert ; 

__attribute__((used)) static int get_geokey_type(int key)
{
    RET_GEOKEY(VERT, vert, type);
    RET_GEOKEY(PROJ, proj, type);
    RET_GEOKEY(GEOG, geog, type);
    RET_GEOKEY(CONF, conf, type);

    return AVERROR_INVALIDDATA;
}