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

/* Variables and functions */
 scalar_t__ cpum_cf_avail () ; 
 scalar_t__ cpum_sf_avail () ; 

const char *perf_pmu_name(void)
{
	if (cpum_cf_avail() || cpum_sf_avail())
		return "CPU-measurement facilities (CPUMF)";
	return "pmu";
}