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
struct zd_usb_tx {scalar_t__ submitted_urbs; int /*<<< orphan*/  lock; int /*<<< orphan*/  submitted_skbs; int /*<<< orphan*/  submitted; int /*<<< orphan*/  enabled; } ;
struct zd_usb {struct zd_usb_tx tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

void zd_usb_disable_tx(struct zd_usb *usb)
{
	struct zd_usb_tx *tx = &usb->tx;
	unsigned long flags;

	atomic_set(&tx->enabled, 0);

	/* kill all submitted tx-urbs */
	usb_kill_anchored_urbs(&tx->submitted);

	spin_lock_irqsave(&tx->lock, flags);
	WARN_ON(!skb_queue_empty(&tx->submitted_skbs));
	WARN_ON(tx->submitted_urbs != 0);
	tx->submitted_urbs = 0;
	spin_unlock_irqrestore(&tx->lock, flags);

	/* The stopped state is ignored, relying on ieee80211_wake_queues()
	 * in a potentionally following zd_usb_enable_tx().
	 */
}