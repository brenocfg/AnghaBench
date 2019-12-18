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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct napi_struct {int /*<<< orphan*/  dev; } ;
typedef  int gro_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
#define  GRO_DROP 132 
#define  GRO_HELD 131 
#define  GRO_MERGED 130 
#define  GRO_MERGED_FREE 129 
#define  GRO_NORMAL 128 
 int /*<<< orphan*/  __eth_type_trans_no_dev_change (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  napi_reuse_skb (struct napi_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_gro_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

gro_result_t napi_frags_finish(struct napi_struct *napi, struct sk_buff *skb,
			       gro_result_t ret)
{
	switch (ret) {
	case GRO_NORMAL:
	case GRO_HELD:
		/*
		 * If this is vlan skb, vlan code previously changed skb->dev to
		 * vlan dev. We need eth_type_trans() to be called with original
		 * device though because otherwise it would change pkt_type.
		 */
		skb->protocol = __eth_type_trans_no_dev_change(skb, napi->dev);

		if (ret == GRO_HELD)
			skb_gro_pull(skb, -ETH_HLEN);
		else if (netif_receive_skb(skb))
			ret = GRO_DROP;
		break;

	case GRO_DROP:
		kfree_skb(skb);
		break;

	case GRO_MERGED_FREE:
		napi_reuse_skb(napi, skb);
		break;

	case GRO_MERGED:
		break;
	}

	return ret;
}