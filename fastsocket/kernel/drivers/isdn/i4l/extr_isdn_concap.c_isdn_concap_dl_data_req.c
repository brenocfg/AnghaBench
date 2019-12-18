#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct concap_proto {struct net_device* net_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  xmit_lock; scalar_t__ huptimer; int /*<<< orphan*/ * netdev; } ;
typedef  TYPE_1__ isdn_net_local ;
typedef  int /*<<< orphan*/  isdn_net_dev ;

/* Variables and functions */
 int /*<<< orphan*/  IX25DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* isdn_net_get_locked_lp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdn_net_writebuf_skb (TYPE_1__*,struct sk_buff*) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isdn_concap_dl_data_req(struct concap_proto *concap, struct sk_buff *skb)
{
	struct net_device *ndev = concap -> net_dev;
	isdn_net_dev *nd = ((isdn_net_local *) netdev_priv(ndev))->netdev;
	isdn_net_local *lp = isdn_net_get_locked_lp(nd);

	IX25DEBUG( "isdn_concap_dl_data_req: %s \n", concap->net_dev->name);
	if (!lp) {
		IX25DEBUG( "isdn_concap_dl_data_req: %s : isdn_net_send_skb returned %d\n", concap -> net_dev -> name, 1);
		return 1;
	}
	lp->huptimer = 0;
	isdn_net_writebuf_skb(lp, skb);
	spin_unlock_bh(&lp->xmit_lock);
	IX25DEBUG( "isdn_concap_dl_data_req: %s : isdn_net_send_skb returned %d\n", concap -> net_dev -> name, 0);
	return 0;
}