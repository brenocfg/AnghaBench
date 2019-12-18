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
struct skb_frag_struct {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_lro_mgr {int features; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 int LRO_F_NAPI ; 
 struct sk_buff* __lro_proc_segment (struct net_lro_mgr*,struct skb_frag_struct*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

void lro_receive_frags(struct net_lro_mgr *lro_mgr,
		       struct skb_frag_struct *frags,
		       int len, int true_size, void *priv, __wsum sum)
{
	struct sk_buff *skb;

	skb = __lro_proc_segment(lro_mgr, frags, len, true_size, NULL, 0,
				 priv, sum);
	if (!skb)
		return;

	if (lro_mgr->features & LRO_F_NAPI)
		netif_receive_skb(skb);
	else
		netif_rx(skb);
}