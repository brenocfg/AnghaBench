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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ CPU_HW_PSTATE ; 
 int /*<<< orphan*/  MSR_FIDVID_STATUS ; 
 int MSR_S_LO_CHANGE_PENDING ; 
 scalar_t__ cpu_family ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int pending_bit_stuck(void)
{
	u32 lo, hi;

	if (cpu_family == CPU_HW_PSTATE)
		return 0;

	rdmsr(MSR_FIDVID_STATUS, lo, hi);
	return lo & MSR_S_LO_CHANGE_PENDING ? 1 : 0;
}