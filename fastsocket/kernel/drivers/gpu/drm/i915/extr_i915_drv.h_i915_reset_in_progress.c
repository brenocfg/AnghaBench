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
struct i915_gpu_error {int /*<<< orphan*/  reset_counter; } ;

/* Variables and functions */
 int I915_RESET_IN_PROGRESS_FLAG ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int unlikely (int) ; 

__attribute__((used)) static inline bool i915_reset_in_progress(struct i915_gpu_error *error)
{
	return unlikely(atomic_read(&error->reset_counter)
			& I915_RESET_IN_PROGRESS_FLAG);
}