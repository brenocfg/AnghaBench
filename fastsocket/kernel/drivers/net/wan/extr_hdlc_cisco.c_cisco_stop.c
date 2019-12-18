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
struct net_device {int dummy; } ;
struct cisco_state {int /*<<< orphan*/  lock; scalar_t__ txseq; scalar_t__ up; int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  hdlc_device ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  netif_dormant_on (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct cisco_state* state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cisco_stop(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	struct cisco_state *st = state(hdlc);
	unsigned long flags;

	del_timer_sync(&st->timer);

	spin_lock_irqsave(&st->lock, flags);
	netif_dormant_on(dev);
	st->up = st->txseq = 0;
	spin_unlock_irqrestore(&st->lock, flags);
}