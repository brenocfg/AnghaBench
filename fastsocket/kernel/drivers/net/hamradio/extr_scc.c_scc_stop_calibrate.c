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
struct scc_channel {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  tx_wdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG ; 
 int /*<<< orphan*/  Outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R6 ; 
 int /*<<< orphan*/  R7 ; 
 int /*<<< orphan*/  RES_EXT_INT ; 
 int /*<<< orphan*/  TX_OFF ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_key_trx (struct scc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wr (struct scc_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scc_stop_calibrate(unsigned long channel)
{
	struct scc_channel *scc = (struct scc_channel *) channel;
	unsigned long flags;
	
	spin_lock_irqsave(&scc->lock, flags);
	del_timer(&scc->tx_wdog);
	scc_key_trx(scc, TX_OFF);
	wr(scc, R6, 0);
	wr(scc, R7, FLAG);
	Outb(scc->ctrl,RES_EXT_INT);	/* reset ext/status interrupts */
	Outb(scc->ctrl,RES_EXT_INT);

	netif_wake_queue(scc->dev);
	spin_unlock_irqrestore(&scc->lock, flags);
}