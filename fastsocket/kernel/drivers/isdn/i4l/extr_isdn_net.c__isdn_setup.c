#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; int tx_queue_len; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * header_ops; } ;
struct TYPE_4__ {int isdn_device; int isdn_channel; int pre_device; int pre_channel; int exclusive; int ppp_slot; int pppbind; int triggercps; int slavedelay; int onhtime; int dialmax; int flags; int cbdelay; int dialtimeout; int dialwait; scalar_t__ dialwait_timer; scalar_t__ dialstarted; int /*<<< orphan*/  hupflags; int /*<<< orphan*/  l3_proto; int /*<<< orphan*/  l2_proto; int /*<<< orphan*/  super_tx_queue; struct TYPE_4__* next; struct TYPE_4__* last; int /*<<< orphan*/  magic; int /*<<< orphan*/  p_encap; } ;
typedef  TYPE_1__ isdn_net_local ;
struct TYPE_5__ {int /*<<< orphan*/  ext_priv_flags; } ;

/* Variables and functions */
 int HZ ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  ISDN_INHUP ; 
 int ISDN_NET_CBHUP ; 
 int ISDN_NET_DM_MANUAL ; 
 int /*<<< orphan*/  ISDN_NET_ENCAP_RAWIP ; 
 int /*<<< orphan*/  ISDN_NET_MAGIC ; 
 int /*<<< orphan*/  ISDN_PROTO_L2_X75I ; 
 int /*<<< orphan*/  ISDN_PROTO_L3_TRANS ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  isdn_netdev_ops ; 
 TYPE_3__* netdev_extended (struct net_device*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _isdn_setup(struct net_device *dev)
{
	isdn_net_local *lp = netdev_priv(dev);

	ether_setup(dev);

	/* Setup the generic properties */
	dev->flags = IFF_NOARP|IFF_POINTOPOINT;

	/* isdn prepends a header in the tx path, can't share skbs */
	netdev_extended(dev)->ext_priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->header_ops = NULL;
	dev->netdev_ops = &isdn_netdev_ops;

	/* for clients with MPPP maybe higher values better */
	dev->tx_queue_len = 30;

	lp->p_encap = ISDN_NET_ENCAP_RAWIP;
	lp->magic = ISDN_NET_MAGIC;
	lp->last = lp;
	lp->next = lp;
	lp->isdn_device = -1;
	lp->isdn_channel = -1;
	lp->pre_device = -1;
	lp->pre_channel = -1;
	lp->exclusive = -1;
	lp->ppp_slot = -1;
	lp->pppbind = -1;
	skb_queue_head_init(&lp->super_tx_queue);
	lp->l2_proto = ISDN_PROTO_L2_X75I;
	lp->l3_proto = ISDN_PROTO_L3_TRANS;
	lp->triggercps = 6000;
	lp->slavedelay = 10 * HZ;
	lp->hupflags = ISDN_INHUP;	/* Do hangup even on incoming calls */
	lp->onhtime = 10;	/* Default hangup-time for saving costs */
	lp->dialmax = 1;
	/* Hangup before Callback, manual dial */
	lp->flags = ISDN_NET_CBHUP | ISDN_NET_DM_MANUAL;
	lp->cbdelay = 25;	/* Wait 5 secs before Callback */
	lp->dialtimeout = -1;  /* Infinite Dial-Timeout */
	lp->dialwait = 5 * HZ; /* Wait 5 sec. after failed dial */
	lp->dialstarted = 0;   /* Jiffies of last dial-start */
	lp->dialwait_timer = 0;  /* Jiffies of earliest next dial-start */
}