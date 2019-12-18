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
struct zd_usb_rx {int /*<<< orphan*/  setup_mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/ * urbs; } ;
struct zd_usb {struct zd_usb_rx rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __zd_usb_disable_rx (struct zd_usb*) ; 
 int /*<<< orphan*/  __zd_usb_enable_rx (struct zd_usb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zd_usb_reset_rx_idle_timer (struct zd_usb*) ; 

__attribute__((used)) static void zd_usb_reset_rx(struct zd_usb *usb)
{
	bool do_reset;
	struct zd_usb_rx *rx = &usb->rx;
	unsigned long flags;

	mutex_lock(&rx->setup_mutex);

	spin_lock_irqsave(&rx->lock, flags);
	do_reset = rx->urbs != NULL;
	spin_unlock_irqrestore(&rx->lock, flags);

	if (do_reset) {
		__zd_usb_disable_rx(usb);
		__zd_usb_enable_rx(usb);
	}

	mutex_unlock(&rx->setup_mutex);

	if (do_reset)
		zd_usb_reset_rx_idle_timer(usb);
}