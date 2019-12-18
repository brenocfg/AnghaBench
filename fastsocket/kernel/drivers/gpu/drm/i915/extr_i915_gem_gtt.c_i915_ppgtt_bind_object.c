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
struct i915_hw_ppgtt {int /*<<< orphan*/  (* insert_entries ) (struct i915_hw_ppgtt*,int /*<<< orphan*/ ,int,int) ;} ;
struct drm_i915_gem_object {TYPE_1__* gtt_space; int /*<<< orphan*/  pages; } ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;
struct TYPE_2__ {int start; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  stub1 (struct i915_hw_ppgtt*,int /*<<< orphan*/ ,int,int) ; 

void i915_ppgtt_bind_object(struct i915_hw_ppgtt *ppgtt,
			    struct drm_i915_gem_object *obj,
			    enum i915_cache_level cache_level)
{
	ppgtt->insert_entries(ppgtt, obj->pages,
			      obj->gtt_space->start >> PAGE_SHIFT,
			      cache_level);
}