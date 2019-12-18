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
struct ucb1400_ts {int irq; int irq_pending; int /*<<< orphan*/  ts_wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ucb1400_hard_irq(int irqnr, void *devid)
{
	struct ucb1400_ts *ucb = devid;

	if (irqnr == ucb->irq) {
		disable_irq_nosync(ucb->irq);
		ucb->irq_pending = 1;
		wake_up(&ucb->ts_wait);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}