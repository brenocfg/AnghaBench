#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  cache_resolve_queue_len; } ;
struct net {TYPE_1__ ipv6; } ;
struct TYPE_9__ {int qlen; } ;
struct TYPE_7__ {TYPE_4__ unresolved; } ;
struct TYPE_8__ {TYPE_2__ unres; } ;
struct mfc6_cache {int mf6c_parent; TYPE_3__ mfc_un; struct mfc6_cache* next; int /*<<< orphan*/  mf6c_mcastgrp; int /*<<< orphan*/  mf6c_origin; } ;
typedef  int /*<<< orphan*/  mifi_t ;
struct TYPE_10__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  MRT6MSG_NOCACHE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct mfc6_cache* ip6mr_cache_alloc_unres (struct net*) ; 
 int /*<<< orphan*/  ip6mr_cache_free (struct mfc6_cache*) ; 
 int ip6mr_cache_report (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmr_do_expire_process (int) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mfc6_net (struct mfc6_cache*) ; 
 int /*<<< orphan*/  mfc_unres_lock ; 
 struct mfc6_cache* mfc_unres_queue ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  skb_queue_tail (TYPE_4__*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ip6mr_cache_unresolved(struct net *net, mifi_t mifi, struct sk_buff *skb)
{
	int err;
	struct mfc6_cache *c;

	spin_lock_bh(&mfc_unres_lock);
	for (c = mfc_unres_queue; c; c = c->next) {
		if (net_eq(mfc6_net(c), net) &&
		    ipv6_addr_equal(&c->mf6c_mcastgrp, &ipv6_hdr(skb)->daddr) &&
		    ipv6_addr_equal(&c->mf6c_origin, &ipv6_hdr(skb)->saddr))
			break;
	}

	if (c == NULL) {
		/*
		 *	Create a new entry if allowable
		 */

		if (atomic_read(&net->ipv6.cache_resolve_queue_len) >= 10 ||
		    (c = ip6mr_cache_alloc_unres(net)) == NULL) {
			spin_unlock_bh(&mfc_unres_lock);

			kfree_skb(skb);
			return -ENOBUFS;
		}

		/*
		 *	Fill in the new cache entry
		 */
		c->mf6c_parent = -1;
		c->mf6c_origin = ipv6_hdr(skb)->saddr;
		c->mf6c_mcastgrp = ipv6_hdr(skb)->daddr;

		/*
		 *	Reflect first query at pim6sd
		 */
		err = ip6mr_cache_report(net, skb, mifi, MRT6MSG_NOCACHE);
		if (err < 0) {
			/* If the report failed throw the cache entry
			   out - Brad Parker
			 */
			spin_unlock_bh(&mfc_unres_lock);

			ip6mr_cache_free(c);
			kfree_skb(skb);
			return err;
		}

		atomic_inc(&net->ipv6.cache_resolve_queue_len);
		c->next = mfc_unres_queue;
		mfc_unres_queue = c;

		ipmr_do_expire_process(1);
	}

	/*
	 *	See if we can append the packet
	 */
	if (c->mfc_un.unres.unresolved.qlen > 3) {
		kfree_skb(skb);
		err = -ENOBUFS;
	} else {
		skb_queue_tail(&c->mfc_un.unres.unresolved, skb);
		err = 0;
	}

	spin_unlock_bh(&mfc_unres_lock);
	return err;
}