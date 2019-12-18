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
struct bfin_twi_iface {int /*<<< orphan*/  lock; int /*<<< orphan*/  timeout_timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bfin_twi_handle_interrupt (struct bfin_twi_iface*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t bfin_twi_interrupt_entry(int irq, void *dev_id)
{
	struct bfin_twi_iface *iface = dev_id;
	unsigned long flags;

	spin_lock_irqsave(&iface->lock, flags);
	del_timer(&iface->timeout_timer);
	bfin_twi_handle_interrupt(iface);
	spin_unlock_irqrestore(&iface->lock, flags);
	return IRQ_HANDLED;
}