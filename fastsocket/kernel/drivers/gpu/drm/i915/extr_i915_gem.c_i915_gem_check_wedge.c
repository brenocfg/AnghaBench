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
struct i915_gpu_error {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 scalar_t__ i915_reset_in_progress (struct i915_gpu_error*) ; 
 scalar_t__ i915_terminally_wedged (struct i915_gpu_error*) ; 

int
i915_gem_check_wedge(struct i915_gpu_error *error,
		     bool interruptible)
{
	if (i915_reset_in_progress(error)) {
		/* Non-interruptible callers can't handle -EAGAIN, hence return
		 * -EIO unconditionally for these. */
		if (!interruptible)
			return -EIO;

		/* Recovery complete, but the reset failed ... */
		if (i915_terminally_wedged(error))
			return -EIO;

		return -EAGAIN;
	}

	return 0;
}