#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tailtime; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_state; int /*<<< orphan*/  txerrs; } ;
struct scc_channel {TYPE_2__ kiss; TYPE_1__ stat; int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  tx_t; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OutReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  RES_Tx_P ; 
 int /*<<< orphan*/  TXS_TIMEOUT ; 
 int /*<<< orphan*/  TxINT_ENAB ; 
 int /*<<< orphan*/  TxUIE ; 
 int /*<<< orphan*/  cl (struct scc_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_discard_buffers (struct scc_channel*) ; 
 int /*<<< orphan*/  scc_start_tx_timer (struct scc_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  t_tail ; 

__attribute__((used)) static void t_maxkeyup(unsigned long channel)
{
	struct scc_channel *scc = (struct scc_channel *) channel;
	unsigned long flags;

	spin_lock_irqsave(&scc->lock, flags);
	/* 
	 * let things settle down before we start to
	 * accept new data.
	 */

	netif_stop_queue(scc->dev);
	scc_discard_buffers(scc);

	del_timer(&scc->tx_t);

	cl(scc, R1, TxINT_ENAB);	/* force an ABORT, but don't */
	cl(scc, R15, TxUIE);		/* count it. */
	OutReg(scc->ctrl, R0, RES_Tx_P);

	spin_unlock_irqrestore(&scc->lock, flags);

	scc->stat.txerrs++;
	scc->stat.tx_state = TXS_TIMEOUT;
	scc_start_tx_timer(scc, t_tail, scc->kiss.tailtime);
}