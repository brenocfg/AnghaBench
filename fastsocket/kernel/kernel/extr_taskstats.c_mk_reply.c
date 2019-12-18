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
typedef  int /*<<< orphan*/  u32 ;
struct taskstats {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
typedef  int /*<<< orphan*/  pid ;

/* Variables and functions */
 int TASKSTATS_TYPE_AGGR_PID ; 
 int TASKSTATS_TYPE_AGGR_TGID ; 
 int TASKSTATS_TYPE_PID ; 
 int /*<<< orphan*/  TASKSTATS_TYPE_STATS ; 
 struct taskstats* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 
 scalar_t__ nla_put (struct sk_buff*,int,int,int /*<<< orphan*/ *) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct taskstats *mk_reply(struct sk_buff *skb, int type, u32 pid)
{
	struct nlattr *na, *ret;
	int aggr;

	aggr = (type == TASKSTATS_TYPE_PID)
			? TASKSTATS_TYPE_AGGR_PID
			: TASKSTATS_TYPE_AGGR_TGID;

	na = nla_nest_start(skb, aggr);
	if (!na)
		goto err;
	if (nla_put(skb, type, sizeof(pid), &pid) < 0)
		goto err;
	ret = nla_reserve(skb, TASKSTATS_TYPE_STATS, sizeof(struct taskstats));
	if (!ret)
		goto err;
	nla_nest_end(skb, na);

	return nla_data(ret);
err:
	return NULL;
}