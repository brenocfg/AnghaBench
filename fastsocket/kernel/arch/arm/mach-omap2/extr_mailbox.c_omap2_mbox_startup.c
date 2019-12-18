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
struct omap_mbox {int dummy; } ;

/* Variables and functions */
 int AUTOIDLE ; 
 int ENODEV ; 
 int /*<<< orphan*/  IRQ_RX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAILBOX_REVISION ; 
 int /*<<< orphan*/  MAILBOX_SYSCONFIG ; 
 int /*<<< orphan*/  MAILBOX_SYSSTATUS ; 
 int RESETDONE ; 
 int SMARTIDLE ; 
 int SOFTRESET ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mbox_ick_handle ; 
 int mbox_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_write_reg (int,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  omap2_mbox_enable_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int omap2_mbox_startup(struct omap_mbox *mbox)
{
	u32 l;
	unsigned long timeout;

	mbox_ick_handle = clk_get(NULL, "mailboxes_ick");
	if (IS_ERR(mbox_ick_handle)) {
		pr_err("Can't get mailboxes_ick\n");
		return -ENODEV;
	}
	clk_enable(mbox_ick_handle);

	mbox_write_reg(SOFTRESET, MAILBOX_SYSCONFIG);
	timeout = jiffies + msecs_to_jiffies(20);
	do {
		l = mbox_read_reg(MAILBOX_SYSSTATUS);
		if (l & RESETDONE)
			break;
	} while (!time_after(jiffies, timeout));

	if (!(l & RESETDONE)) {
		pr_err("Can't take mmu out of reset\n");
		return -ENODEV;
	}

	l = mbox_read_reg(MAILBOX_REVISION);
	pr_info("omap mailbox rev %d.%d\n", (l & 0xf0) >> 4, (l & 0x0f));

	l = SMARTIDLE | AUTOIDLE;
	mbox_write_reg(l, MAILBOX_SYSCONFIG);

	omap2_mbox_enable_irq(mbox, IRQ_RX);

	return 0;
}