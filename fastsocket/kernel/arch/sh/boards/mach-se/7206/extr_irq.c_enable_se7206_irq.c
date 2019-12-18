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
 int /*<<< orphan*/  INTC_IPR01 ; 
 int /*<<< orphan*/  INTMSK0 ; 
 int /*<<< orphan*/  INTMSK1 ; 
#define  IRQ0_IRQ 130 
#define  IRQ1_IRQ 129 
#define  IRQ3_IRQ 128 
 unsigned short ctrl_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outw (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_se7206_irq(unsigned int irq)
{
	unsigned short val;
	unsigned short value = (0x0001 << 4 * (3 - (IRQ0_IRQ - irq)));
	unsigned short msk0,msk1;

	/* Set priority in IPR back to original value */
	val = ctrl_inw(INTC_IPR01);
	val |= value;
	ctrl_outw(val, INTC_IPR01);

	/* FPGA mask reset */
	msk0 = ctrl_inw(INTMSK0);
	msk1 = ctrl_inw(INTMSK1);

	switch (irq) {
	case IRQ0_IRQ:
		msk0 &= ~0x0010;
		break;
	case IRQ1_IRQ:
		msk0 &= ~0x000f;
		break;
	case IRQ3_IRQ:
		msk0 &= ~0x0f00;
		msk1 &= ~0x00ff;
		break;
	}
	ctrl_outw(msk0, INTMSK0);
	ctrl_outw(msk1, INTMSK1);
}