#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {struct net_device* dev; } ;
struct rtmsg {int rtm_flags; } ;
struct rtable {int /*<<< orphan*/  rt_dst; int /*<<< orphan*/  rt_src; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct mr_table {int dummy; } ;
struct mfc_cache {int /*<<< orphan*/  mfc_flags; } ;
struct iphdr {int ihl; scalar_t__ version; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MFC_NOTIFY ; 
 int RTM_F_NOTIFY ; 
 int /*<<< orphan*/  RT_TABLE_DEFAULT ; 
 int __ipmr_fill_mroute (struct mr_table*,struct sk_buff*,struct mfc_cache*,struct rtmsg*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 struct mfc_cache* ipmr_cache_find (struct mr_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipmr_cache_unresolved (struct mr_table*,int,struct sk_buff*) ; 
 int ipmr_find_vif (struct mr_table*,struct net_device*) ; 
 struct mr_table* ipmr_get_table (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrt_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 

int ipmr_get_route(struct net *net,
		   struct sk_buff *skb, struct rtmsg *rtm, int nowait)
{
	int err;
	struct mr_table *mrt;
	struct mfc_cache *cache;
	struct rtable *rt = skb_rtable(skb);

	mrt = ipmr_get_table(net, RT_TABLE_DEFAULT);
	if (mrt == NULL)
		return -ENOENT;

	read_lock(&mrt_lock);
	cache = ipmr_cache_find(mrt, rt->rt_src, rt->rt_dst);

	if (cache == NULL) {
		struct sk_buff *skb2;
		struct iphdr *iph;
		struct net_device *dev;
		int vif;

		if (nowait) {
			read_unlock(&mrt_lock);
			return -EAGAIN;
		}

		dev = skb->dev;
		if (dev == NULL || (vif = ipmr_find_vif(mrt, dev)) < 0) {
			read_unlock(&mrt_lock);
			return -ENODEV;
		}
		skb2 = skb_clone(skb, GFP_ATOMIC);
		if (!skb2) {
			read_unlock(&mrt_lock);
			return -ENOMEM;
		}

		skb_push(skb2, sizeof(struct iphdr));
		skb_reset_network_header(skb2);
		iph = ip_hdr(skb2);
		iph->ihl = sizeof(struct iphdr) >> 2;
		iph->saddr = rt->rt_src;
		iph->daddr = rt->rt_dst;
		iph->version = 0;
		err = ipmr_cache_unresolved(mrt, vif, skb2);
		read_unlock(&mrt_lock);
		return err;
	}

	if (!nowait && (rtm->rtm_flags&RTM_F_NOTIFY))
		cache->mfc_flags |= MFC_NOTIFY;
	err = __ipmr_fill_mroute(mrt, skb, cache, rtm);
	read_unlock(&mrt_lock);
	return err;
}