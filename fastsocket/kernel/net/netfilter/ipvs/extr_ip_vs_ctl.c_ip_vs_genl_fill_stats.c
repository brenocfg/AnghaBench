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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  outbps; int /*<<< orphan*/  inbps; int /*<<< orphan*/  outpps; int /*<<< orphan*/  inpps; int /*<<< orphan*/  cps; int /*<<< orphan*/  outbytes; int /*<<< orphan*/  inbytes; int /*<<< orphan*/  outpkts; int /*<<< orphan*/  inpkts; int /*<<< orphan*/  conns; } ;
struct ip_vs_stats {int /*<<< orphan*/  lock; TYPE_1__ ustats; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IPVS_STATS_ATTR_CONNS ; 
 int /*<<< orphan*/  IPVS_STATS_ATTR_CPS ; 
 int /*<<< orphan*/  IPVS_STATS_ATTR_INBPS ; 
 int /*<<< orphan*/  IPVS_STATS_ATTR_INBYTES ; 
 int /*<<< orphan*/  IPVS_STATS_ATTR_INPKTS ; 
 int /*<<< orphan*/  IPVS_STATS_ATTR_INPPS ; 
 int /*<<< orphan*/  IPVS_STATS_ATTR_OUTBPS ; 
 int /*<<< orphan*/  IPVS_STATS_ATTR_OUTBYTES ; 
 int /*<<< orphan*/  IPVS_STATS_ATTR_OUTPKTS ; 
 int /*<<< orphan*/  IPVS_STATS_ATTR_OUTPPS ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_U64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ip_vs_genl_fill_stats(struct sk_buff *skb, int container_type,
				 struct ip_vs_stats *stats)
{
	struct nlattr *nl_stats = nla_nest_start(skb, container_type);
	if (!nl_stats)
		return -EMSGSIZE;

	spin_lock_bh(&stats->lock);

	NLA_PUT_U32(skb, IPVS_STATS_ATTR_CONNS, stats->ustats.conns);
	NLA_PUT_U32(skb, IPVS_STATS_ATTR_INPKTS, stats->ustats.inpkts);
	NLA_PUT_U32(skb, IPVS_STATS_ATTR_OUTPKTS, stats->ustats.outpkts);
	NLA_PUT_U64(skb, IPVS_STATS_ATTR_INBYTES, stats->ustats.inbytes);
	NLA_PUT_U64(skb, IPVS_STATS_ATTR_OUTBYTES, stats->ustats.outbytes);
	NLA_PUT_U32(skb, IPVS_STATS_ATTR_CPS, stats->ustats.cps);
	NLA_PUT_U32(skb, IPVS_STATS_ATTR_INPPS, stats->ustats.inpps);
	NLA_PUT_U32(skb, IPVS_STATS_ATTR_OUTPPS, stats->ustats.outpps);
	NLA_PUT_U32(skb, IPVS_STATS_ATTR_INBPS, stats->ustats.inbps);
	NLA_PUT_U32(skb, IPVS_STATS_ATTR_OUTBPS, stats->ustats.outbps);

	spin_unlock_bh(&stats->lock);

	nla_nest_end(skb, nl_stats);

	return 0;

nla_put_failure:
	spin_unlock_bh(&stats->lock);
	nla_nest_cancel(skb, nl_stats);
	return -EMSGSIZE;
}