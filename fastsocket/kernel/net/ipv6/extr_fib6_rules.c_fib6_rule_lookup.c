#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* ip6_null_entry; int /*<<< orphan*/  fib6_rules_ops; } ;
struct net {TYPE_3__ ipv6; } ;
struct flowi {int dummy; } ;
struct fib_lookup_arg {struct dst_entry* result; scalar_t__ rule; int /*<<< orphan*/  lookup_ptr; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  pol_lookup_t ;
struct TYPE_4__ {struct dst_entry dst; } ;
struct TYPE_5__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_hold (struct dst_entry*) ; 
 int /*<<< orphan*/  fib_rule_put (scalar_t__) ; 
 int /*<<< orphan*/  fib_rules_lookup (int /*<<< orphan*/ ,struct flowi*,int,struct fib_lookup_arg*) ; 

struct dst_entry *fib6_rule_lookup(struct net *net, struct flowi *fl,
				   int flags, pol_lookup_t lookup)
{
	struct fib_lookup_arg arg = {
		.lookup_ptr = lookup,
	};

	fib_rules_lookup(net->ipv6.fib6_rules_ops, fl, flags, &arg);
	if (arg.rule)
		fib_rule_put(arg.rule);

	if (arg.result)
		return arg.result;

	dst_hold(&net->ipv6.ip6_null_entry->u.dst);
	return &net->ipv6.ip6_null_entry->u.dst;
}