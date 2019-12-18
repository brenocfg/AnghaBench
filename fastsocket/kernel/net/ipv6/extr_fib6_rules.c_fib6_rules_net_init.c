#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* fib6_rules_ops; } ;
struct net {TYPE_1__ ipv6; } ;
struct TYPE_8__ {int /*<<< orphan*/  rules_list; struct net* fro_net; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FIB_RULE_PERMANENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RT6_TABLE_LOCAL ; 
 int /*<<< orphan*/  RT6_TABLE_MAIN ; 
 int /*<<< orphan*/  fib6_rules_ops_template ; 
 int fib_default_rule_add (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib_rules_cleanup_ops (TYPE_2__*) ; 
 int fib_rules_register (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fib6_rules_net_init(struct net *net)
{
	int err = -ENOMEM;

	net->ipv6.fib6_rules_ops = kmemdup(&fib6_rules_ops_template,
					   sizeof(*net->ipv6.fib6_rules_ops),
					   GFP_KERNEL);
	if (!net->ipv6.fib6_rules_ops)
		goto out;

	net->ipv6.fib6_rules_ops->fro_net = net;
	INIT_LIST_HEAD(&net->ipv6.fib6_rules_ops->rules_list);

	err = fib_default_rule_add(net->ipv6.fib6_rules_ops, 0,
				   RT6_TABLE_LOCAL, FIB_RULE_PERMANENT);
	if (err)
		goto out_fib6_rules_ops;

	err = fib_default_rule_add(net->ipv6.fib6_rules_ops,
				   0x7FFE, RT6_TABLE_MAIN, 0);
	if (err)
		goto out_fib6_default_rule_add;

	err = fib_rules_register(net->ipv6.fib6_rules_ops);
	if (err)
		goto out_fib6_default_rule_add;
out:
	return err;

out_fib6_default_rule_add:
	fib_rules_cleanup_ops(net->ipv6.fib6_rules_ops);
out_fib6_rules_ops:
	kfree(net->ipv6.fib6_rules_ops);
	goto out;
}