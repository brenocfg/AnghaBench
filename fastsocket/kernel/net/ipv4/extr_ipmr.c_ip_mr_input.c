#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct mr_table {scalar_t__ mroute_sk; } ;
struct mfc_cache {int dummy; } ;
struct TYPE_5__ {scalar_t__ router_alert; } ;
struct TYPE_8__ {int flags; TYPE_1__ opt; } ;
struct TYPE_7__ {scalar_t__ protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_6__ {int rt_flags; int /*<<< orphan*/  fl; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_4__* IPCB (struct sk_buff*) ; 
 scalar_t__ IPPROTO_IGMP ; 
 int IPSKB_FORWARDED ; 
 int RTCF_LOCAL ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 scalar_t__ ip_call_ra_chain (struct sk_buff*) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 int ip_local_deliver (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_mr_forward (struct net*,struct mr_table*,struct sk_buff*,struct mfc_cache*,int) ; 
 struct mfc_cache* ipmr_cache_find (struct mr_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipmr_cache_unresolved (struct mr_table*,int,struct sk_buff*) ; 
 int ipmr_fib_lookup (struct net*,int /*<<< orphan*/ *,struct mr_table**) ; 
 int ipmr_find_vif (struct mr_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mrt_lock ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  raw_rcv (scalar_t__,struct sk_buff*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_rtable (struct sk_buff*) ; 

int ip_mr_input(struct sk_buff *skb)
{
	struct mfc_cache *cache;
	struct net *net = dev_net(skb->dev);
	int local = skb_rtable(skb)->rt_flags & RTCF_LOCAL;
	struct mr_table *mrt;
	int err;

	/* Packet is looped back after forward, it should not be
	   forwarded second time, but still can be delivered locally.
	 */
	if (IPCB(skb)->flags&IPSKB_FORWARDED)
		goto dont_forward;

	err = ipmr_fib_lookup(net, &skb_rtable(skb)->fl, &mrt);
	if (err < 0) {
		kfree_skb(skb);
		return err;
	}

	if (!local) {
		    if (IPCB(skb)->opt.router_alert) {
			    if (ip_call_ra_chain(skb))
				    return 0;
		    } else if (ip_hdr(skb)->protocol == IPPROTO_IGMP){
			    /* IGMPv1 (and broken IGMPv2 implementations sort of
			       Cisco IOS <= 11.2(8)) do not put router alert
			       option to IGMP packets destined to routable
			       groups. It is very bad, because it means
			       that we can forward NO IGMP messages.
			     */
			    read_lock(&mrt_lock);
			    if (mrt->mroute_sk) {
				    nf_reset(skb);
				    raw_rcv(mrt->mroute_sk, skb);
				    read_unlock(&mrt_lock);
				    return 0;
			    }
			    read_unlock(&mrt_lock);
		    }
	}

	read_lock(&mrt_lock);
	cache = ipmr_cache_find(mrt, ip_hdr(skb)->saddr, ip_hdr(skb)->daddr);

	/*
	 *	No usable cache entry
	 */
	if (cache == NULL) {
		int vif;

		if (local) {
			struct sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);
			ip_local_deliver(skb);
			if (skb2 == NULL) {
				read_unlock(&mrt_lock);
				return -ENOBUFS;
			}
			skb = skb2;
		}

		vif = ipmr_find_vif(mrt, skb->dev);
		if (vif >= 0) {
			int err = ipmr_cache_unresolved(mrt, vif, skb);
			read_unlock(&mrt_lock);

			return err;
		}
		read_unlock(&mrt_lock);
		kfree_skb(skb);
		return -ENODEV;
	}

	ip_mr_forward(net, mrt, skb, cache, local);

	read_unlock(&mrt_lock);

	if (local)
		return ip_local_deliver(skb);

	return 0;

dont_forward:
	if (local)
		return ip_local_deliver(skb);
	kfree_skb(skb);
	return 0;
}