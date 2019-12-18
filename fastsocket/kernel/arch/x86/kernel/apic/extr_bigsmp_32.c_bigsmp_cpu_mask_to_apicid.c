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
 unsigned int bigsmp_cpu_to_logical_apicid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_first (struct cpumask const*) ; 

__attribute__((used)) static unsigned int bigsmp_cpu_mask_to_apicid(const struct cpumask *cpumask)
{
	return bigsmp_cpu_to_logical_apicid(cpumask_first(cpumask));
}