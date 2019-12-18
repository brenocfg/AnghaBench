#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tci; } ;
struct sw_flow_key {TYPE_1__ eth; } ;
struct sk_buff {int len; scalar_t__ data; } ;
typedef  int __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VLAN_TAG_PRESENT ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int parse_vlan(struct sk_buff *skb, struct sw_flow_key *key)
{
	struct qtag_prefix {
		__be16 eth_type; /* ETH_P_8021Q */
		__be16 tci;
	};
	struct qtag_prefix *qp;

	if (unlikely(skb->len < sizeof(struct qtag_prefix) + sizeof(__be16)))
		return 0;

	if (unlikely(!pskb_may_pull(skb, sizeof(struct qtag_prefix) +
					 sizeof(__be16))))
		return -ENOMEM;

	qp = (struct qtag_prefix *) skb->data;
	key->eth.tci = qp->tci | htons(VLAN_TAG_PRESENT);
	__skb_pull(skb, sizeof(struct qtag_prefix));

	return 0;
}