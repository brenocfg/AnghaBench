#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_aborted_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct arcnet_local {int timed_out; int cur_tx; int intmask; scalar_t__ last_timeout; int /*<<< orphan*/  lasttrans_dest; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACOMMAND (int) ; 
 int /*<<< orphan*/  AINTMASK (int) ; 
 int ASTATUS () ; 
 int /*<<< orphan*/  BUGMSG (int /*<<< orphan*/ ,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_EXTRA ; 
 int EXCNAKflag ; 
 int HZ ; 
 int NOTXcmd ; 
 int TXFREEflag ; 
 scalar_t__ jiffies ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

void arcnet_timeout(struct net_device *dev)
{
	unsigned long flags;
	struct arcnet_local *lp = netdev_priv(dev);
	int status = ASTATUS();
	char *msg;

	spin_lock_irqsave(&lp->lock, flags);
	if (status & TXFREEflag) {	/* transmit _DID_ finish */
		msg = " - missed IRQ?";
	} else {
		msg = "";
		dev->stats.tx_aborted_errors++;
		lp->timed_out = 1;
		ACOMMAND(NOTXcmd | (lp->cur_tx << 3));
	}
	dev->stats.tx_errors++;

	/* make sure we didn't miss a TX or a EXC NAK IRQ */
	AINTMASK(0);
	lp->intmask |= TXFREEflag|EXCNAKflag;
	AINTMASK(lp->intmask);
	
	spin_unlock_irqrestore(&lp->lock, flags);

	if (time_after(jiffies, lp->last_timeout + 10*HZ)) {
		BUGMSG(D_EXTRA, "tx timed out%s (status=%Xh, intmask=%Xh, dest=%02Xh)\n",
		       msg, status, lp->intmask, lp->lasttrans_dest);
		lp->last_timeout = jiffies;
	}

	if (lp->cur_tx == -1)
		netif_wake_queue(dev);
}