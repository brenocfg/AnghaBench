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
struct zd_usb_tx {int /*<<< orphan*/  lock; scalar_t__ stopped; scalar_t__ submitted_urbs; int /*<<< orphan*/  enabled; } ;
struct zd_usb {struct zd_usb_tx tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zd_usb_to_hw (struct zd_usb*) ; 

void zd_usb_enable_tx(struct zd_usb *usb)
{
	unsigned long flags;
	struct zd_usb_tx *tx = &usb->tx;

	spin_lock_irqsave(&tx->lock, flags);
	atomic_set(&tx->enabled, 1);
	tx->submitted_urbs = 0;
	ieee80211_wake_queues(zd_usb_to_hw(usb));
	tx->stopped = 0;
	spin_unlock_irqrestore(&tx->lock, flags);
}