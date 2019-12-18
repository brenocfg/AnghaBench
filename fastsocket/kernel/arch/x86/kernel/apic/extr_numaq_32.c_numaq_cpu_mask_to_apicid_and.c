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
struct cpumask {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int
numaq_cpu_mask_to_apicid_and(const struct cpumask *cpumask,
			     const struct cpumask *andmask)
{
	return 0x0F;
}