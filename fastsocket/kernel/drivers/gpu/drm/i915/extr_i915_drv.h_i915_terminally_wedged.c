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
 scalar_t__ I915_WEDGED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool i915_terminally_wedged(struct i915_gpu_error *error)
{
	return atomic_read(&error->reset_counter) == I915_WEDGED;
}