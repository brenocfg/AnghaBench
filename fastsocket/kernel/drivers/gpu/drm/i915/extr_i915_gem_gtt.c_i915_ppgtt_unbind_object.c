#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i915_hw_ppgtt {int /*<<< orphan*/  (* clear_range ) (struct i915_hw_ppgtt*,int,int) ;} ;
struct TYPE_4__ {int size; } ;
struct drm_i915_gem_object {TYPE_2__ base; TYPE_1__* gtt_space; } ;
struct TYPE_3__ {int start; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  stub1 (struct i915_hw_ppgtt*,int,int) ; 

void i915_ppgtt_unbind_object(struct i915_hw_ppgtt *ppgtt,
			      struct drm_i915_gem_object *obj)
{
	ppgtt->clear_range(ppgtt,
			   obj->gtt_space->start >> PAGE_SHIFT,
			   obj->base.size >> PAGE_SHIFT);
}