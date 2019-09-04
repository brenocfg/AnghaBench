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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int kpc_get_all_cpus_counters (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int kpc_get_curcpu_counters (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

int
kpc_get_cpu_counters(boolean_t all_cpus, uint32_t classes,
                     int *curcpu, uint64_t *buf)
{
	assert(buf);

	/*
	 * Unlike reading the current CPU counters, reading counters from all
	 * CPUs is architecture dependent. This allows kpc to make the most of
	 * the platform if memory mapped registers is supported.
	 */
	if (all_cpus)
		return kpc_get_all_cpus_counters(classes, curcpu, buf);
	else
		return kpc_get_curcpu_counters(classes, curcpu, buf);
}