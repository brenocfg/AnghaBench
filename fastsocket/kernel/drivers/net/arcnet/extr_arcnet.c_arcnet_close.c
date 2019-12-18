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
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* close ) (struct net_device*) ;} ;
struct arcnet_local {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACOMMAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AINTMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NORXcmd ; 
 int /*<<< orphan*/  NOTXcmd ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

int arcnet_close(struct net_device *dev)
{
	struct arcnet_local *lp = netdev_priv(dev);

	netif_stop_queue(dev);

	/* flush TX and disable RX */
	AINTMASK(0);
	ACOMMAND(NOTXcmd);	/* stop transmit */
	ACOMMAND(NORXcmd);	/* disable receive */
	mdelay(1);

	/* shut down the card */
	lp->hw.close(dev);
	module_put(lp->hw.owner);
	return 0;
}