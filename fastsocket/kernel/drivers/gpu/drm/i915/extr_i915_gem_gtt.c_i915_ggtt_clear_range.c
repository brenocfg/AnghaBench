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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_gtt_clear_range (unsigned int,unsigned int) ; 

__attribute__((used)) static void i915_ggtt_clear_range(struct drm_device *dev,
				  unsigned int first_entry,
				  unsigned int num_entries)
{
	intel_gtt_clear_range(first_entry, num_entries);
}