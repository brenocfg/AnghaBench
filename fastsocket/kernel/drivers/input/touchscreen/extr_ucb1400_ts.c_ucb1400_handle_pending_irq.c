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
struct ucb1400_ts {int /*<<< orphan*/  irq; TYPE_1__* ts_idev; int /*<<< orphan*/  ac97; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_IE_CLEAR ; 
 int /*<<< orphan*/  UCB_IE_STATUS ; 
 unsigned int UCB_IE_TSPX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 unsigned int ucb1400_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ucb1400_ts_irq_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ucb1400_handle_pending_irq(struct ucb1400_ts *ucb)
{
	unsigned int isr;

	isr = ucb1400_reg_read(ucb->ac97, UCB_IE_STATUS);
	ucb1400_reg_write(ucb->ac97, UCB_IE_CLEAR, isr);
	ucb1400_reg_write(ucb->ac97, UCB_IE_CLEAR, 0);

	if (isr & UCB_IE_TSPX)
		ucb1400_ts_irq_disable(ucb->ac97);
	else
		dev_dbg(&ucb->ts_idev->dev, "ucb1400: unexpected IE_STATUS = %#x\n", isr);
	enable_irq(ucb->irq);
}