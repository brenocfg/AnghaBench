#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u_char ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;
struct concap_proto {TYPE_2__* pops; } ;
typedef  int netdev_tx_t ;
struct TYPE_16__ {int flags; scalar_t__ dialwait_timer; scalar_t__ dialstarted; scalar_t__ dialtimeout; scalar_t__ dialwait; int pre_channel; int dialstate; scalar_t__ p_encap; int /*<<< orphan*/  msn; int /*<<< orphan*/  pre_device; int /*<<< orphan*/  l3_proto; int /*<<< orphan*/  l2_proto; scalar_t__* phone; TYPE_1__* netdev; } ;
typedef  TYPE_3__ isdn_net_local ;
struct TYPE_15__ {int (* encap_and_xmit ) (struct concap_proto*,struct sk_buff*) ;} ;
struct TYPE_14__ {struct concap_proto* cprot; } ;
struct TYPE_13__ {int /*<<< orphan*/  lock; scalar_t__ net_verbose; } ;

/* Variables and functions */
 int ISDN_NET_CONNECTED ; 
 scalar_t__ ISDN_NET_DIALMODE (TYPE_3__) ; 
 scalar_t__ ISDN_NET_DM_AUTO ; 
 scalar_t__ ISDN_NET_ENCAP_SYNCPPP ; 
 int /*<<< orphan*/  ISDN_USAGE_NET ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 TYPE_11__* dev ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  isdn_dumppkt (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int isdn_get_free_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdn_net_adjust_hdr (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  isdn_net_bind_channel (TYPE_3__*,int) ; 
 int /*<<< orphan*/  isdn_net_device_stop_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  isdn_net_dial () ; 
 int /*<<< orphan*/  isdn_net_log_skb (struct sk_buff*,TYPE_3__*) ; 
 int /*<<< orphan*/  isdn_net_unbind_channel (TYPE_3__*) ; 
 int /*<<< orphan*/  isdn_net_unreachable (struct net_device*,struct sk_buff*,char*) ; 
 int isdn_net_xmit (struct net_device*,struct sk_buff*) ; 
 scalar_t__ isdn_ppp_autodial_filter (struct sk_buff*,TYPE_3__*) ; 
 scalar_t__ isdn_ppp_bind (TYPE_3__*) ; 
 int /*<<< orphan*/  isdn_ppp_free (TYPE_3__*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct concap_proto*,struct sk_buff*) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static netdev_tx_t
isdn_net_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	isdn_net_local *lp = (isdn_net_local *) netdev_priv(ndev);
#ifdef CONFIG_ISDN_X25
	struct concap_proto * cprot = lp -> netdev -> cprot;
/* At this point hard_start_xmit() passes control to the encapsulation
   protocol (if present).
   For X.25 auto-dialing is completly bypassed because:
   - It does not conform with the semantics of a reliable datalink
     service as needed by X.25 PLP.
   - I don't want that the interface starts dialing when the network layer
     sends a message which requests to disconnect the lapb link (or if it
     sends any other message not resulting in data transmission).
   Instead, dialing will be initiated by the encapsulation protocol entity
   when a dl_establish request is received from the upper layer.
*/
	if (cprot && cprot -> pops) {
		int ret = cprot -> pops -> encap_and_xmit ( cprot , skb);

		if (ret)
			netif_stop_queue(ndev);
		return ret;
	} else
#endif
	/* auto-dialing xmit function */
	{
#ifdef ISDN_DEBUG_NET_DUMP
		u_char *buf;
#endif
		isdn_net_adjust_hdr(skb, ndev);
#ifdef ISDN_DEBUG_NET_DUMP
		buf = skb->data;
		isdn_dumppkt("S:", buf, skb->len, 40);
#endif

		if (!(lp->flags & ISDN_NET_CONNECTED)) {
			int chi;
			/* only do autodial if allowed by config */
			if (!(ISDN_NET_DIALMODE(*lp) == ISDN_NET_DM_AUTO)) {
				isdn_net_unreachable(ndev, skb, "dial rejected: interface not in dialmode `auto'");
				dev_kfree_skb(skb);
				return NETDEV_TX_OK;
			}
			if (lp->phone[1]) {
				ulong flags;

				if(lp->dialwait_timer <= 0)
					if(lp->dialstarted > 0 && lp->dialtimeout > 0 && time_before(jiffies, lp->dialstarted + lp->dialtimeout + lp->dialwait))
						lp->dialwait_timer = lp->dialstarted + lp->dialtimeout + lp->dialwait;

				if(lp->dialwait_timer > 0) {
					if(time_before(jiffies, lp->dialwait_timer)) {
						isdn_net_unreachable(ndev, skb, "dial rejected: retry-time not reached");
						dev_kfree_skb(skb);
						return NETDEV_TX_OK;
					} else
						lp->dialwait_timer = 0;
				}
				/* Grab a free ISDN-Channel */
				spin_lock_irqsave(&dev->lock, flags);
				if (((chi =
				     isdn_get_free_channel(
					 		ISDN_USAGE_NET,
							lp->l2_proto,
							lp->l3_proto,
							lp->pre_device,
						 	lp->pre_channel,
							lp->msn)
							) < 0) &&
					((chi =
				     isdn_get_free_channel(
					 		ISDN_USAGE_NET,
							lp->l2_proto,
							lp->l3_proto,
							lp->pre_device,
							lp->pre_channel^1,
							lp->msn)
							) < 0)) {
					spin_unlock_irqrestore(&dev->lock, flags);
					isdn_net_unreachable(ndev, skb,
							   "No channel");
					dev_kfree_skb(skb);
					return NETDEV_TX_OK;
				}
				/* Log packet, which triggered dialing */
				if (dev->net_verbose)
					isdn_net_log_skb(skb, lp);
				lp->dialstate = 1;
				/* Connect interface with channel */
				isdn_net_bind_channel(lp, chi);
#ifdef CONFIG_ISDN_PPP
				if (lp->p_encap == ISDN_NET_ENCAP_SYNCPPP) {
					/* no 'first_skb' handling for syncPPP */
					if (isdn_ppp_bind(lp) < 0) {
						dev_kfree_skb(skb);
						isdn_net_unbind_channel(lp);
						spin_unlock_irqrestore(&dev->lock, flags);
						return NETDEV_TX_OK;	/* STN (skb to nirvana) ;) */
					}
#ifdef CONFIG_IPPP_FILTER
					if (isdn_ppp_autodial_filter(skb, lp)) {
						isdn_ppp_free(lp);
						isdn_net_unbind_channel(lp);
						spin_unlock_irqrestore(&dev->lock, flags);
						isdn_net_unreachable(ndev, skb, "dial rejected: packet filtered");
						dev_kfree_skb(skb);
						return NETDEV_TX_OK;
					}
#endif
					spin_unlock_irqrestore(&dev->lock, flags);
					isdn_net_dial();	/* Initiate dialing */
					netif_stop_queue(ndev);
					return NETDEV_TX_BUSY;	/* let upper layer requeue skb packet */
				}
#endif
				/* Initiate dialing */
				spin_unlock_irqrestore(&dev->lock, flags);
				isdn_net_dial();
				isdn_net_device_stop_queue(lp);
				return NETDEV_TX_BUSY;
			} else {
				isdn_net_unreachable(ndev, skb,
						     "No phone number");
				dev_kfree_skb(skb);
				return NETDEV_TX_OK;
			}
		} else {
			/* Device is connected to an ISDN channel */ 
			ndev->trans_start = jiffies;
			if (!lp->dialstate) {
				/* ISDN connection is established, try sending */
				int ret;
				ret = (isdn_net_xmit(ndev, skb));
				if(ret) netif_stop_queue(ndev);
				return ret;
			} else
				netif_stop_queue(ndev);
		}
	}
	return NETDEV_TX_BUSY;
}