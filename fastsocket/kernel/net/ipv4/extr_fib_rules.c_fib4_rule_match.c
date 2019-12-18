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
struct flowi {int fl4_dst; int fl4_src; scalar_t__ fl4_tos; } ;
struct fib_rule {int dummy; } ;
struct fib4_rule {int src; int srcmask; int dst; int dstmask; scalar_t__ tos; } ;
typedef  int __be32 ;

/* Variables and functions */

__attribute__((used)) static int fib4_rule_match(struct fib_rule *rule, struct flowi *fl, int flags)
{
	struct fib4_rule *r = (struct fib4_rule *) rule;
	__be32 daddr = fl->fl4_dst;
	__be32 saddr = fl->fl4_src;

	if (((saddr ^ r->src) & r->srcmask) ||
	    ((daddr ^ r->dst) & r->dstmask))
		return 0;

	if (r->tos && (r->tos != fl->fl4_tos))
		return 0;

	return 1;
}