#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * res; int /*<<< orphan*/  car_rmr; } ;
struct TYPE_4__ {TYPE_1__ im_clkrst; } ;

/* Variables and functions */
 int MSR_DR ; 
 int MSR_EE ; 
 int MSR_IR ; 
 int MSR_ME ; 
 int /*<<< orphan*/  RMR_CSRE ; 
 TYPE_2__* cpm2_immr ; 
 int /*<<< orphan*/  in_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  setbits32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void pq2_restart(char *cmd)
{
	local_irq_disable();
	setbits32(&cpm2_immr->im_clkrst.car_rmr, RMR_CSRE);

	/* Clear the ME,EE,IR & DR bits in MSR to cause checkstop */
	mtmsr(mfmsr() & ~(MSR_ME | MSR_EE | MSR_IR | MSR_DR));
	in_8(&cpm2_immr->im_clkrst.res[0]);

	panic("Restart failed\n");
}