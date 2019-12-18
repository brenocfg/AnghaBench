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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ HV_EOK ; 
 int /*<<< orphan*/  HV_N2_PERF_SPARC_CTL ; 
 unsigned long sun4v_niagara2_setperf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  write_pcr (scalar_t__) ; 

__attribute__((used)) static void n2_pcr_write(u64 val)
{
	unsigned long ret;

	ret = sun4v_niagara2_setperf(HV_N2_PERF_SPARC_CTL, val);
	if (val != HV_EOK)
		write_pcr(val);
}