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
struct flowi {int dummy; } ;
struct fib_lookup_arg {int /*<<< orphan*/  rule; struct dn_fib_res* result; } ;
struct dn_fib_res {int /*<<< orphan*/  r; } ;

/* Variables and functions */
 int /*<<< orphan*/  dn_fib_rules_ops ; 
 int fib_rules_lookup (int /*<<< orphan*/ *,struct flowi*,int /*<<< orphan*/ ,struct fib_lookup_arg*) ; 

int dn_fib_lookup(struct flowi *flp, struct dn_fib_res *res)
{
	struct fib_lookup_arg arg = {
		.result = res,
	};
	int err;

	err = fib_rules_lookup(&dn_fib_rules_ops, flp, 0, &arg);
	res->r = arg.rule;

	return err;
}