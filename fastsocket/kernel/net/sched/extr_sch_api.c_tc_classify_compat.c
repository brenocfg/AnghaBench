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
struct tcf_result {int dummy; } ;
struct tcf_proto {scalar_t__ protocol; int (* classify ) (struct sk_buff*,struct tcf_proto*,struct tcf_result*) ;struct tcf_proto* next; } ;
struct sk_buff {scalar_t__ protocol; scalar_t__ tc_verd; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ALL ; 
 scalar_t__ SET_TC_VERD (scalar_t__,int /*<<< orphan*/ ) ; 
 int TC_ACT_RECLASSIFY ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*,struct tcf_proto*,struct tcf_result*) ; 

int tc_classify_compat(struct sk_buff *skb, struct tcf_proto *tp,
		       struct tcf_result *res)
{
	__be16 protocol = skb->protocol;
	int err = 0;

	for (; tp; tp = tp->next) {
		if ((tp->protocol == protocol ||
		     tp->protocol == htons(ETH_P_ALL)) &&
		    (err = tp->classify(skb, tp, res)) >= 0) {
#ifdef CONFIG_NET_CLS_ACT
			if (err != TC_ACT_RECLASSIFY && skb->tc_verd)
				skb->tc_verd = SET_TC_VERD(skb->tc_verd, 0);
#endif
			return err;
		}
	}
	return -1;
}