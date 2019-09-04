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

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_TSC_DEADLINE ; 
 int /*<<< orphan*/  wrmsr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
lapic_set_tsc_deadline_timer(uint64_t deadline)
{
	/* Don't bother disarming: wrmsr64(MSR_IA32_TSC_DEADLINE, 0); */
	wrmsr64(MSR_IA32_TSC_DEADLINE, deadline);
}