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
struct net_device {int dummy; } ;
struct TYPE_2__ {int command; } ;
struct i596_private {TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA () ; 
 int CUC_ABORT ; 
 int RX_ABORT ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  i596_cleanup_cmd (struct net_device*) ; 
 int /*<<< orphan*/  i596_rx (struct net_device*) ; 
 scalar_t__ i596_timeout (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  init_i596 (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static void i596_reset(struct net_device *dev, struct i596_private *lp, int ioaddr) {

	if (lp->scb.command && i596_timeout(dev, "i596_reset", 100))
		;

	netif_stop_queue(dev);

	lp->scb.command = CUC_ABORT | RX_ABORT;
	CA();
	barrier();

	/* wait for shutdown */
	if (lp->scb.command && i596_timeout(dev, "i596_reset(2)", 400))
		;

	i596_cleanup_cmd(dev);
	i596_rx(dev);

	netif_start_queue(dev);
	/*dev_kfree_skb(skb, FREE_WRITE);*/
	init_i596(dev);
}