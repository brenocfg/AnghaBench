#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcf_exts {TYPE_1__* action; } ;
struct tcf_ext_map {scalar_t__ police; scalar_t__ action; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ TCA_OLD_COMPAT ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,scalar_t__) ; 
 scalar_t__ tcf_action_dump (struct sk_buff*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_action_dump_old (struct sk_buff*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tcf_exts_dump(struct sk_buff *skb, struct tcf_exts *exts,
		  const struct tcf_ext_map *map)
{
#ifdef CONFIG_NET_CLS_ACT
	if (map->action && exts->action) {
		/*
		 * again for backward compatible mode - we want
		 * to work with both old and new modes of entering
		 * tc data even if iproute2  was newer - jhs
		 */
		struct nlattr *nest;

		if (exts->action->type != TCA_OLD_COMPAT) {
			nest = nla_nest_start(skb, map->action);
			if (nest == NULL)
				goto nla_put_failure;
			if (tcf_action_dump(skb, exts->action, 0, 0) < 0)
				goto nla_put_failure;
			nla_nest_end(skb, nest);
		} else if (map->police) {
			nest = nla_nest_start(skb, map->police);
			if (nest == NULL)
				goto nla_put_failure;
			if (tcf_action_dump_old(skb, exts->action, 0, 0) < 0)
				goto nla_put_failure;
			nla_nest_end(skb, nest);
		}
	}
#endif
	return 0;
nla_put_failure: __attribute__ ((unused))
	return -1;
}