#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_local_map {scalar_t__ type; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; } ;
struct drm_device {TYPE_1__* agp; } ;
struct TYPE_2__ {scalar_t__ cant_use_aperture; } ;

/* Variables and functions */
 scalar_t__ _DRM_AGP ; 
 int /*<<< orphan*/  agp_remap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_device*) ; 
 scalar_t__ drm_core_has_AGP (struct drm_device*) ; 
 int /*<<< orphan*/  ioremap_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void drm_core_ioremap_wc(struct drm_local_map *map, struct drm_device *dev)
{
	if (drm_core_has_AGP(dev) &&
	    dev->agp && dev->agp->cant_use_aperture && map->type == _DRM_AGP)
		map->handle = agp_remap(map->offset, map->size, dev);
	else
		map->handle = ioremap_wc(map->offset, map->size);
}