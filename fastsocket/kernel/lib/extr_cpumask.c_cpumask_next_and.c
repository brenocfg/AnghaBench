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
 int cpumask_next (int,struct cpumask const*) ; 
 scalar_t__ cpumask_test_cpu (int,struct cpumask const*) ; 
 int nr_cpu_ids ; 

int cpumask_next_and(int n, const struct cpumask *src1p,
		     const struct cpumask *src2p)
{
	while ((n = cpumask_next(n, src1p)) < nr_cpu_ids)
		if (cpumask_test_cpu(n, src2p))
			break;
	return n;
}