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
typedef  scalar_t__ u32 ;
struct xt_target_param {TYPE_1__* target; struct xt_NFQ_info_v1* targinfo; } ;
struct xt_NFQ_info_v1 {int queues_total; scalar_t__ queuenum; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ NFPROTO_IPV4 ; 
 scalar_t__ NFPROTO_IPV6 ; 
 unsigned int NF_QUEUE_NR (scalar_t__) ; 
 int hash_v4 (struct sk_buff*) ; 
 int hash_v6 (struct sk_buff*) ; 

__attribute__((used)) static unsigned int
nfqueue_tg_v1(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct xt_NFQ_info_v1 *info = par->targinfo;
	u32 queue = info->queuenum;

	if (info->queues_total > 1) {
		if (par->target->family == NFPROTO_IPV4)
			queue = hash_v4(skb) % info->queues_total + queue;
#if defined(CONFIG_IP6_NF_IPTABLES) || defined(CONFIG_IP6_NF_IPTABLES_MODULE)
		else if (par->target->family == NFPROTO_IPV6)
			queue = hash_v6(skb) % info->queues_total + queue;
#endif
	}
	return NF_QUEUE_NR(queue);
}