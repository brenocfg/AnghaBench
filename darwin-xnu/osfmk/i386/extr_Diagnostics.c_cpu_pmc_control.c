#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cpu_fixed_pmcs_enabled; } ;
typedef  TYPE_1__ cpu_data_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int CR4_PCE ; 
 TYPE_1__* current_cpu_datap () ; 
 int get_cr4 () ; 
 int /*<<< orphan*/  set_cr4 (int) ; 
 int /*<<< orphan*/  wrmsr64 (int,int) ; 

void cpu_pmc_control(void *enablep) {
#if !MONOTONIC
	boolean_t enable = *(boolean_t *)enablep;
	cpu_data_t	*cdp = current_cpu_datap();

	if (enable) {
		wrmsr64(0x38F, 0x70000000FULL);
		wrmsr64(0x38D, 0x333);
		set_cr4(get_cr4() | CR4_PCE);

	} else {
		wrmsr64(0x38F, 0);
		wrmsr64(0x38D, 0);
		set_cr4((get_cr4() & ~CR4_PCE));
	}
	cdp->cpu_fixed_pmcs_enabled = enable;
#else /* !MONOTONIC */
#pragma unused(enablep)
#endif /* MONOTONIC */
}