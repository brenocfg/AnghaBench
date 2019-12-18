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
struct sk_buff {int dummy; } ;
struct net_lro_mgr {int features; } ;

/* Variables and functions */
 int LRO_F_NAPI ; 
 scalar_t__ __lro_proc_skb (struct net_lro_mgr*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

void lro_receive_skb(struct net_lro_mgr *lro_mgr,
		     struct sk_buff *skb,
		     void *priv)
{
	if (__lro_proc_skb(lro_mgr, skb, NULL, 0, priv)) {
		if (lro_mgr->features & LRO_F_NAPI)
			netif_receive_skb(skb);
		else
			netif_rx(skb);
	}
}