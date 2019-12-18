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
struct flowi {scalar_t__ iif; int mark; } ;
struct fib_rules_ops {int (* match ) (struct fib_rule*,struct flowi*,int) ;} ;
struct fib_rule {scalar_t__ ifindex; int mark; int mark_mask; int flags; } ;

/* Variables and functions */
 int FIB_RULE_INVERT ; 
 int stub1 (struct fib_rule*,struct flowi*,int) ; 

__attribute__((used)) static int fib_rule_match(struct fib_rule *rule, struct fib_rules_ops *ops,
			  struct flowi *fl, int flags)
{
	int ret = 0;

	if (rule->ifindex && (rule->ifindex != fl->iif))
		goto out;

	if ((rule->mark ^ fl->mark) & rule->mark_mask)
		goto out;

	ret = ops->match(rule, fl, flags);
out:
	return (rule->flags & FIB_RULE_INVERT) ? !ret : ret;
}