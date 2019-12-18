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
struct scc_channel {int /*<<< orphan*/  tx_wdog; int /*<<< orphan*/  tx_t; int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrl; } ;
struct net_device {scalar_t__ ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  Outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  scc_discard_buffers (struct scc_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wr (struct scc_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scc_net_close(struct net_device *dev)
{
	struct scc_channel *scc = (struct scc_channel *) dev->ml_priv;
	unsigned long flags;

	netif_stop_queue(dev);

	spin_lock_irqsave(&scc->lock, flags);	
	Outb(scc->ctrl,0);		/* Make sure pointer is written */
	wr(scc,R1,0);			/* disable interrupts */
	wr(scc,R3,0);
	spin_unlock_irqrestore(&scc->lock, flags);

	del_timer_sync(&scc->tx_t);
	del_timer_sync(&scc->tx_wdog);
	
	scc_discard_buffers(scc);

	return 0;
}