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
struct fib_table {int (* tb_lookup ) (struct fib_table*,struct flowi*,struct fib_result*) ;} ;
struct fib_rule {int action; int /*<<< orphan*/  table; int /*<<< orphan*/  fr_net; } ;
struct fib_result {int dummy; } ;
struct fib_lookup_arg {scalar_t__ result; } ;

/* Variables and functions */
 int EACCES ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENETUNREACH ; 
#define  FR_ACT_BLACKHOLE 131 
#define  FR_ACT_PROHIBIT 130 
#define  FR_ACT_TO_TBL 129 
#define  FR_ACT_UNREACHABLE 128 
 struct fib_table* fib_get_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct fib_table*,struct flowi*,struct fib_result*) ; 

__attribute__((used)) static int fib4_rule_action(struct fib_rule *rule, struct flowi *flp,
			    int flags, struct fib_lookup_arg *arg)
{
	int err = -EAGAIN;
	struct fib_table *tbl;

	switch (rule->action) {
	case FR_ACT_TO_TBL:
		break;

	case FR_ACT_UNREACHABLE:
		err = -ENETUNREACH;
		goto errout;

	case FR_ACT_PROHIBIT:
		err = -EACCES;
		goto errout;

	case FR_ACT_BLACKHOLE:
	default:
		err = -EINVAL;
		goto errout;
	}

	if ((tbl = fib_get_table(rule->fr_net, rule->table)) == NULL)
		goto errout;

	err = tbl->tb_lookup(tbl, flp, (struct fib_result *) arg->result);
	if (err > 0)
		err = -EAGAIN;
errout:
	return err;
}