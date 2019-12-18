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
struct drm_i915_gem_object {int fenced_gpu_access; scalar_t__ last_fenced_seqno; int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int i915_wait_seqno (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
i915_gem_object_wait_fence(struct drm_i915_gem_object *obj)
{
	if (obj->last_fenced_seqno) {
		int ret = i915_wait_seqno(obj->ring, obj->last_fenced_seqno);
		if (ret)
			return ret;

		obj->last_fenced_seqno = 0;
	}

	obj->fenced_gpu_access = false;
	return 0;
}