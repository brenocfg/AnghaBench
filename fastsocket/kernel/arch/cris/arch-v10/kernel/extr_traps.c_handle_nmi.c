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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int IO_STATE (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* R_IRQ_MASK0_RD ; 
 int /*<<< orphan*/  active ; 
 int /*<<< orphan*/  nmi_handler (struct pt_regs*) ; 
 int /*<<< orphan*/  nmi_pin ; 

void handle_nmi(struct pt_regs *regs)
{
	if (nmi_handler)
		nmi_handler(regs);

	/* Wait until nmi is no longer active. (We enable NMI immediately after
	   returning from this function, and we don't want it happening while
	   exiting from the NMI interrupt handler.) */
	while (*R_IRQ_MASK0_RD & IO_STATE(R_IRQ_MASK0_RD, nmi_pin, active))
		;
}