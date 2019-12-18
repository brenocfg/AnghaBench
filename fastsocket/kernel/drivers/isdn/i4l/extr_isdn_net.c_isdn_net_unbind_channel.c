#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int isdn_device; int isdn_channel; int /*<<< orphan*/  flags; scalar_t__ dialstate; TYPE_1__* netdev; int /*<<< orphan*/  master; int /*<<< orphan*/  super_tx_queue; } ;
typedef  TYPE_2__ isdn_net_local ;
struct TYPE_7__ {int /*<<< orphan*/ ** st_netdev; int /*<<< orphan*/ ** rx_netdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_NET_CONNECTED ; 
 int /*<<< orphan*/  ISDN_USAGE_NET ; 
 TYPE_4__* dev ; 
 size_t isdn_dc2minor (int,int) ; 
 int /*<<< orphan*/  isdn_free_channel (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_reset_all_tx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isdn_net_unbind_channel(isdn_net_local * lp)
{
	skb_queue_purge(&lp->super_tx_queue);

	if (!lp->master) {	/* reset only master device */
		/* Moral equivalent of dev_purge_queues():
		   BEWARE! This chunk of code cannot be called from hardware
		   interrupt handler. I hope it is true. --ANK
		 */
		qdisc_reset_all_tx(lp->netdev->dev);
	}
	lp->dialstate = 0;
	dev->rx_netdev[isdn_dc2minor(lp->isdn_device, lp->isdn_channel)] = NULL;
	dev->st_netdev[isdn_dc2minor(lp->isdn_device, lp->isdn_channel)] = NULL;
	if (lp->isdn_device != -1 && lp->isdn_channel != -1)
		isdn_free_channel(lp->isdn_device, lp->isdn_channel,
				  ISDN_USAGE_NET);
	lp->flags &= ~ISDN_NET_CONNECTED;
	lp->isdn_device = -1;
	lp->isdn_channel = -1;
}