#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ dev; scalar_t__ len; } ;
struct net {int dummy; } ;
struct mr_table {TYPE_2__* vif_table; scalar_t__ mroute_do_pim; scalar_t__ mroute_do_assert; } ;
struct TYPE_9__ {int* ttls; int maxvif; int minvif; scalar_t__ last_assert; int /*<<< orphan*/  wrong_if; int /*<<< orphan*/  bytes; int /*<<< orphan*/  pkt; } ;
struct TYPE_10__ {TYPE_3__ res; } ;
struct mfc_cache {int mfc_parent; TYPE_4__ mfc_un; } ;
struct TYPE_12__ {scalar_t__ ttl; } ;
struct TYPE_7__ {scalar_t__ iif; } ;
struct TYPE_11__ {TYPE_1__ fl; } ;
struct TYPE_8__ {scalar_t__ dev; int /*<<< orphan*/  bytes_in; int /*<<< orphan*/  pkt_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IGMPMSG_WRONGVIF ; 
 scalar_t__ MFC_ASSERT_THRESH ; 
 TYPE_6__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipmr_cache_report (struct mr_table*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int ipmr_find_vif (struct mr_table*,scalar_t__) ; 
 int /*<<< orphan*/  ipmr_queue_xmit (struct net*,struct mr_table*,struct sk_buff*,struct mfc_cache*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_5__* skb_rtable (struct sk_buff*) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ip_mr_forward(struct net *net, struct mr_table *mrt,
			 struct sk_buff *skb, struct mfc_cache *cache,
			 int local)
{
	int psend = -1;
	int vif, ct;

	vif = cache->mfc_parent;
	cache->mfc_un.res.pkt++;
	cache->mfc_un.res.bytes += skb->len;

	/*
	 * Wrong interface: drop packet and (maybe) send PIM assert.
	 */
	if (mrt->vif_table[vif].dev != skb->dev) {
		int true_vifi;

		if (skb_rtable(skb)->fl.iif == 0) {
			/* It is our own packet, looped back.
			   Very complicated situation...

			   The best workaround until routing daemons will be
			   fixed is not to redistribute packet, if it was
			   send through wrong interface. It means, that
			   multicast applications WILL NOT work for
			   (S,G), which have default multicast route pointing
			   to wrong oif. In any case, it is not a good
			   idea to use multicasting applications on router.
			 */
			goto dont_forward;
		}

		cache->mfc_un.res.wrong_if++;
		true_vifi = ipmr_find_vif(mrt, skb->dev);

		if (true_vifi >= 0 && mrt->mroute_do_assert &&
		    /* pimsm uses asserts, when switching from RPT to SPT,
		       so that we cannot check that packet arrived on an oif.
		       It is bad, but otherwise we would need to move pretty
		       large chunk of pimd to kernel. Ough... --ANK
		     */
		    (mrt->mroute_do_pim ||
		     cache->mfc_un.res.ttls[true_vifi] < 255) &&
		    time_after(jiffies,
			       cache->mfc_un.res.last_assert + MFC_ASSERT_THRESH)) {
			cache->mfc_un.res.last_assert = jiffies;
			ipmr_cache_report(mrt, skb, true_vifi, IGMPMSG_WRONGVIF);
		}
		goto dont_forward;
	}

	mrt->vif_table[vif].pkt_in++;
	mrt->vif_table[vif].bytes_in += skb->len;

	/*
	 *	Forward the frame
	 */
	for (ct = cache->mfc_un.res.maxvif-1; ct >= cache->mfc_un.res.minvif; ct--) {
		if (ip_hdr(skb)->ttl > cache->mfc_un.res.ttls[ct]) {
			if (psend != -1) {
				struct sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);
				if (skb2)
					ipmr_queue_xmit(net, mrt, skb2, cache,
							psend);
			}
			psend = ct;
		}
	}
	if (psend != -1) {
		if (local) {
			struct sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);
			if (skb2)
				ipmr_queue_xmit(net, mrt, skb2, cache, psend);
		} else {
			ipmr_queue_xmit(net, mrt, skb, cache, psend);
			return 0;
		}
	}

dont_forward:
	if (!local)
		kfree_skb(skb);
	return 0;
}