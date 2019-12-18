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
struct zd_usb_rx {unsigned int urbs_count; int /*<<< orphan*/  lock; struct urb** urbs; } ;
struct zd_usb {struct zd_usb_rx rx; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_rx_urb (struct urb*) ; 
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 

__attribute__((used)) static void __zd_usb_disable_rx(struct zd_usb *usb)
{
	int i;
	unsigned long flags;
	struct urb **urbs;
	unsigned int count;
	struct zd_usb_rx *rx = &usb->rx;

	spin_lock_irqsave(&rx->lock, flags);
	urbs = rx->urbs;
	count = rx->urbs_count;
	spin_unlock_irqrestore(&rx->lock, flags);
	if (!urbs)
		return;

	for (i = 0; i < count; i++) {
		usb_kill_urb(urbs[i]);
		free_rx_urb(urbs[i]);
	}
	kfree(urbs);

	spin_lock_irqsave(&rx->lock, flags);
	rx->urbs = NULL;
	rx->urbs_count = 0;
	spin_unlock_irqrestore(&rx->lock, flags);
}