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
struct i915_gpu_error {int /*<<< orphan*/  reset_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EIO ; 
 scalar_t__ EXIT_COND ; 
 int HZ ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int
i915_gem_wait_for_error(struct i915_gpu_error *error)
{
	int ret;

#define EXIT_COND (!i915_reset_in_progress(error) || \
		   i915_terminally_wedged(error))
	if (EXIT_COND)
		return 0;

	/*
	 * Only wait 10 seconds for the gpu reset to complete to avoid hanging
	 * userspace. If it takes that long something really bad is going on and
	 * we should simply try to bail out and fail as gracefully as possible.
	 */
	ret = wait_event_interruptible_timeout(error->reset_queue,
					       EXIT_COND,
					       10*HZ);
	if (ret == 0) {
		DRM_ERROR("Timed out waiting for the gpu reset to complete\n");
		return -EIO;
	} else if (ret < 0) {
		return ret;
	}
#undef EXIT_COND

	return 0;
}