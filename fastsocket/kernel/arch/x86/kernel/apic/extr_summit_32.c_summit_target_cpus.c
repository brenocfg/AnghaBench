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
 struct cpumask const* cpumask_of (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct cpumask *summit_target_cpus(void)
{
	/* CPU_MASK_ALL (0xff) has undefined behaviour with
	 * dest_LowestPrio mode logical clustered apic interrupt routing
	 * Just start on cpu 0.  IRQ balancing will spread load
	 */
	return cpumask_of(0);
}