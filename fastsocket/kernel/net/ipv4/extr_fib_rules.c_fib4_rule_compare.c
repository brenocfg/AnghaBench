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
struct nlattr {int dummy; } ;
struct fib_rule_hdr {scalar_t__ src_len; scalar_t__ dst_len; scalar_t__ tos; } ;
struct fib_rule {int dummy; } ;
struct fib4_rule {scalar_t__ src_len; scalar_t__ dst_len; scalar_t__ tos; scalar_t__ tclassid; scalar_t__ src; scalar_t__ dst; } ;

/* Variables and functions */
 size_t FRA_DST ; 
 size_t FRA_FLOW ; 
 size_t FRA_SRC ; 
 scalar_t__ nla_get_be32 (struct nlattr*) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static int fib4_rule_compare(struct fib_rule *rule, struct fib_rule_hdr *frh,
			     struct nlattr **tb)
{
	struct fib4_rule *rule4 = (struct fib4_rule *) rule;

	if (frh->src_len && (rule4->src_len != frh->src_len))
		return 0;

	if (frh->dst_len && (rule4->dst_len != frh->dst_len))
		return 0;

	if (frh->tos && (rule4->tos != frh->tos))
		return 0;

#ifdef CONFIG_NET_CLS_ROUTE
	if (tb[FRA_FLOW] && (rule4->tclassid != nla_get_u32(tb[FRA_FLOW])))
		return 0;
#endif

	if (frh->src_len && (rule4->src != nla_get_be32(tb[FRA_SRC])))
		return 0;

	if (frh->dst_len && (rule4->dst != nla_get_be32(tb[FRA_DST])))
		return 0;

	return 1;
}