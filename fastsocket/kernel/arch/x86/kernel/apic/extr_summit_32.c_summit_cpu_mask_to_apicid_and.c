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
typedef  struct cpumask const* cpumask_var_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  alloc_cpumask_var (struct cpumask const**,int /*<<< orphan*/ ) ; 
 struct cpumask const* cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (struct cpumask const*,struct cpumask const*,struct cpumask const*) ; 
 int /*<<< orphan*/  free_cpumask_var (struct cpumask const*) ; 
 int summit_cpu_mask_to_apicid (struct cpumask const*) ; 
 int summit_cpu_to_logical_apicid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int summit_cpu_mask_to_apicid_and(const struct cpumask *inmask,
			      const struct cpumask *andmask)
{
	int apicid = summit_cpu_to_logical_apicid(0);
	cpumask_var_t cpumask;

	if (!alloc_cpumask_var(&cpumask, GFP_ATOMIC))
		return apicid;

	cpumask_and(cpumask, inmask, andmask);
	cpumask_and(cpumask, cpumask, cpu_online_mask);
	apicid = summit_cpu_mask_to_apicid(cpumask);

	free_cpumask_var(cpumask);

	return apicid;
}