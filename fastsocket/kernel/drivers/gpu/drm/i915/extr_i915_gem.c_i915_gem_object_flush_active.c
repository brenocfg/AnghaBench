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
struct drm_i915_gem_object {int /*<<< orphan*/  ring; int /*<<< orphan*/  last_read_seqno; scalar_t__ active; } ;

/* Variables and functions */
 int i915_gem_check_olr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_retire_requests_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i915_gem_object_flush_active(struct drm_i915_gem_object *obj)
{
	int ret;

	if (obj->active) {
		ret = i915_gem_check_olr(obj->ring, obj->last_read_seqno);
		if (ret)
			return ret;

		i915_gem_retire_requests_ring(obj->ring);
	}

	return 0;
}