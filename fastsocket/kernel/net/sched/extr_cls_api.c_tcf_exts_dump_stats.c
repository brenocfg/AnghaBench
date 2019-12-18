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
struct tcf_exts {scalar_t__ action; } ;
struct tcf_ext_map {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ tcf_action_copy_stats (struct sk_buff*,scalar_t__,int) ; 

int tcf_exts_dump_stats(struct sk_buff *skb, struct tcf_exts *exts,
			const struct tcf_ext_map *map)
{
#ifdef CONFIG_NET_CLS_ACT
	if (exts->action)
		if (tcf_action_copy_stats(skb, exts->action, 1) < 0)
			goto nla_put_failure;
#endif
	return 0;
nla_put_failure: __attribute__ ((unused))
	return -1;
}