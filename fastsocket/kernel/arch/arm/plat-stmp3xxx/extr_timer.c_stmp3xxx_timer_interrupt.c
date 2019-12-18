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
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BM_TIMROT_TIMCTRLn_IRQ ; 
 int BM_TIMROT_TIMCTRLn_IRQ_EN ; 
 scalar_t__ HW_TIMROT_TIMCOUNT1 ; 
 scalar_t__ HW_TIMROT_TIMCTRL0 ; 
 scalar_t__ HW_TIMROT_TIMCTRL1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ REGS_TIMROT_BASE ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  stmp3xxx_clearl (int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 

__attribute__((used)) static irqreturn_t
stmp3xxx_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *c = dev_id;

	/* timer 0 */
	if (__raw_readl(REGS_TIMROT_BASE + HW_TIMROT_TIMCTRL0) &
			BM_TIMROT_TIMCTRLn_IRQ) {
		stmp3xxx_clearl(BM_TIMROT_TIMCTRLn_IRQ,
				REGS_TIMROT_BASE + HW_TIMROT_TIMCTRL0);
		c->event_handler(c);
	}

	/* timer 1 */
	else if (__raw_readl(REGS_TIMROT_BASE + HW_TIMROT_TIMCTRL1)
			& BM_TIMROT_TIMCTRLn_IRQ) {
		stmp3xxx_clearl(BM_TIMROT_TIMCTRLn_IRQ,
				REGS_TIMROT_BASE + HW_TIMROT_TIMCTRL1);
		stmp3xxx_clearl(BM_TIMROT_TIMCTRLn_IRQ_EN,
				REGS_TIMROT_BASE + HW_TIMROT_TIMCTRL1);
		__raw_writel(0xFFFF, REGS_TIMROT_BASE + HW_TIMROT_TIMCOUNT1);
	}

	return IRQ_HANDLED;
}