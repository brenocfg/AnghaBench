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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_2__ {int (* init ) (TYPE_1__*) ;} ;
struct fritzcard {scalar_t__ type; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  irqcnt; int /*<<< orphan*/  lock; TYPE_1__ isac; } ;

/* Variables and functions */
 scalar_t__ AVM_FRITZ_PCIV2 ; 
 int DEBUG_HW ; 
 int EIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  ISACX_CMDRD ; 
 int /*<<< orphan*/  ISACX_MASK ; 
 int /*<<< orphan*/  ISAC_CMDR ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  WriteISAC_V1 (struct fritzcard*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteISAC_V2 (struct fritzcard*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avm_fritz_interrupt ; 
 int /*<<< orphan*/  avm_fritzv2_interrupt ; 
 int /*<<< orphan*/  clear_pending_hdlc_ints (struct fritzcard*) ; 
 int debug ; 
 int /*<<< orphan*/  enable_hwirq (struct fritzcard*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fritzcard*) ; 
 int /*<<< orphan*/  inithdlc (struct fritzcard*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fritzcard*) ; 
 int /*<<< orphan*/  reset_avm (struct fritzcard*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static int
init_card(struct fritzcard *fc)
{
	int		ret, cnt = 3;
	u_long		flags;

	reset_avm(fc); /* disable IRQ */
	if (fc->type == AVM_FRITZ_PCIV2)
		ret = request_irq(fc->irq, avm_fritzv2_interrupt,
			IRQF_SHARED, fc->name, fc);
	else
		ret = request_irq(fc->irq, avm_fritz_interrupt,
			IRQF_SHARED, fc->name, fc);
	if (ret) {
		pr_info("%s: couldn't get interrupt %d\n",
			fc->name, fc->irq);
		return ret;
	}
	while (cnt--) {
		spin_lock_irqsave(&fc->lock, flags);
		ret = fc->isac.init(&fc->isac);
		if (ret) {
			spin_unlock_irqrestore(&fc->lock, flags);
			pr_info("%s: ISAC init failed with %d\n",
				fc->name, ret);
			break;
		}
		clear_pending_hdlc_ints(fc);
		inithdlc(fc);
		enable_hwirq(fc);
		/* RESET Receiver and Transmitter */
		if (AVM_FRITZ_PCIV2 == fc->type) {
			WriteISAC_V2(fc, ISACX_MASK, 0);
			WriteISAC_V2(fc, ISACX_CMDRD, 0x41);
		} else {
			WriteISAC_V1(fc, ISAC_MASK, 0);
			WriteISAC_V1(fc, ISAC_CMDR, 0x41);
		}
		spin_unlock_irqrestore(&fc->lock, flags);
		/* Timeout 10ms */
		msleep_interruptible(10);
		if (debug & DEBUG_HW)
			pr_notice("%s: IRQ %d count %d\n", fc->name,
				fc->irq, fc->irqcnt);
		if (!fc->irqcnt) {
			pr_info("%s: IRQ(%d) getting no IRQs during init %d\n",
				fc->name, fc->irq, 3 - cnt);
			reset_avm(fc);
		} else
			return 0;
	}
	free_irq(fc->irq, fc);
	return -EIO;
}