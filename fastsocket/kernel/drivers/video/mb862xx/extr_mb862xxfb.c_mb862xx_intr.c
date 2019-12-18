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
struct mb862xxfb_par {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ BT_CARMINE ; 
 int GC_CTRL_INT_MASK ; 
 int GC_CTRL_STATUS ; 
 int GC_IMASK ; 
 int GC_IST ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ctrl ; 
 int /*<<< orphan*/  host ; 
 unsigned long inreg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outreg (int /*<<< orphan*/ ,int,unsigned long) ; 

irqreturn_t mb862xx_intr(int irq, void *dev_id)
{
	struct mb862xxfb_par *par = (struct mb862xxfb_par *) dev_id;
	unsigned long reg_ist, mask;

	if (!par)
		return IRQ_NONE;

	if (par->type == BT_CARMINE) {
		/* Get Interrupt Status */
		reg_ist = inreg(ctrl, GC_CTRL_STATUS);
		mask = inreg(ctrl, GC_CTRL_INT_MASK);
		if (reg_ist == 0)
			return IRQ_HANDLED;

		reg_ist &= mask;
		if (reg_ist == 0)
			return IRQ_HANDLED;

		/* Clear interrupt status */
		outreg(ctrl, 0x0, reg_ist);
	} else {
		/* Get status */
		reg_ist = inreg(host, GC_IST);
		mask = inreg(host, GC_IMASK);

		reg_ist &= mask;
		if (reg_ist == 0)
			return IRQ_HANDLED;

		/* Clear status */
		outreg(host, GC_IST, ~reg_ist);
	}
	return IRQ_HANDLED;
}