#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ key; } ;
struct TYPE_7__ {TYPE_2__ hash; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; TYPE_3__ map_list; TYPE_1__* dev; } ;
struct drm_i915_gem_object {int fault_mappable; TYPE_4__ base; } ;
typedef  int loff_t ;
struct TYPE_5__ {scalar_t__ dev_mapping; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  unmap_mapping_range (scalar_t__,int,int /*<<< orphan*/ ,int) ; 

void
i915_gem_release_mmap(struct drm_i915_gem_object *obj)
{
	if (!obj->fault_mappable)
		return;

	if (obj->base.dev->dev_mapping)
		unmap_mapping_range(obj->base.dev->dev_mapping,
				    (loff_t)obj->base.map_list.hash.key<<PAGE_SHIFT,
				    obj->base.size, 1);

	obj->fault_mappable = false;
}