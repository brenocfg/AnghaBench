#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTSTS0 ; 
 int /*<<< orphan*/  INTSTS1 ; 
#define  IRQ0_IRQ 130 
#define  IRQ1_IRQ 129 
#define  IRQ3_IRQ 128 
 int IRQ_DISABLED ; 
 int IRQ_INPROGRESS ; 
 unsigned short ctrl_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outw (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_se7206_irq (unsigned int) ; 
 TYPE_1__* irq_desc ; 

__attribute__((used)) static void eoi_se7206_irq(unsigned int irq)
{
	unsigned short sts0,sts1;

	if (!(irq_desc[irq].status & (IRQ_DISABLED|IRQ_INPROGRESS)))
		enable_se7206_irq(irq);
	/* FPGA isr clear */
	sts0 = ctrl_inw(INTSTS0);
	sts1 = ctrl_inw(INTSTS1);

	switch (irq) {
	case IRQ0_IRQ:
		sts0 &= ~0x0010;
		break;
	case IRQ1_IRQ:
		sts0 &= ~0x000f;
		break;
	case IRQ3_IRQ:
		sts0 &= ~0x0f00;
		sts1 &= ~0x00ff;
		break;
	}
	ctrl_outw(sts0, INTSTS0);
	ctrl_outw(sts1, INTSTS1);
}