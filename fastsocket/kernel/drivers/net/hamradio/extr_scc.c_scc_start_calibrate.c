#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct scc_channel {int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrl; TYPE_1__ tx_wdog; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  Outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R6 ; 
 int /*<<< orphan*/  R7 ; 
 int /*<<< orphan*/  RES_EXT_INT ; 
 int /*<<< orphan*/  TX_ON ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_discard_buffers (struct scc_channel*) ; 
 int /*<<< orphan*/  scc_key_trx (struct scc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_stop_calibrate ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wr (struct scc_channel*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void
scc_start_calibrate(struct scc_channel *scc, int duration, unsigned char pattern)
{
	unsigned long flags;
	
	spin_lock_irqsave(&scc->lock, flags);
	netif_stop_queue(scc->dev);
	scc_discard_buffers(scc);

	del_timer(&scc->tx_wdog);

	scc->tx_wdog.data = (unsigned long) scc;
	scc->tx_wdog.function = scc_stop_calibrate;
	scc->tx_wdog.expires = jiffies + HZ*duration;
	add_timer(&scc->tx_wdog);

	/* This doesn't seem to work. Why not? */	
	wr(scc, R6, 0);
	wr(scc, R7, pattern);

	/* 
	 * Don't know if this works. 
	 * Damn, where is my Z8530 programming manual...? 
	 */

	Outb(scc->ctrl,RES_EXT_INT);	/* reset ext/status interrupts */
	Outb(scc->ctrl,RES_EXT_INT);

	scc_key_trx(scc, TX_ON);
	spin_unlock_irqrestore(&scc->lock, flags);
}