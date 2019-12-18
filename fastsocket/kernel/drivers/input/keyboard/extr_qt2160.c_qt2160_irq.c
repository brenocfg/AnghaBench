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
struct qt2160_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  dwork; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  __cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t qt2160_irq(int irq, void *_qt2160)
{
	struct qt2160_data *qt2160 = _qt2160;
	unsigned long flags;

	spin_lock_irqsave(&qt2160->lock, flags);

	__cancel_delayed_work(&qt2160->dwork);
	schedule_delayed_work(&qt2160->dwork, 0);

	spin_unlock_irqrestore(&qt2160->lock, flags);

	return IRQ_HANDLED;
}