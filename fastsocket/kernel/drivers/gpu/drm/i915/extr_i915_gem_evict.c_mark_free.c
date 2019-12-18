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
struct list_head {int dummy; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  gtt_space; int /*<<< orphan*/  exec_list; scalar_t__ pin_count; } ;

/* Variables and functions */
 int drm_mm_scan_add_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static bool
mark_free(struct drm_i915_gem_object *obj, struct list_head *unwind)
{
	if (obj->pin_count)
		return false;

	list_add(&obj->exec_list, unwind);
	return drm_mm_scan_add_block(obj->gtt_space);
}