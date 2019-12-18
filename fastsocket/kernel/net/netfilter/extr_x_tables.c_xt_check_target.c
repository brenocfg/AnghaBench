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
typedef  int /*<<< orphan*/  used ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct xt_tgchk_param {size_t family; int hook_mask; TYPE_1__* target; int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  allow ;
struct TYPE_2__ {int hooks; int /*<<< orphan*/  (* checkentry ) (struct xt_tgchk_param*) ;int /*<<< orphan*/  proto; int /*<<< orphan*/  name; int /*<<< orphan*/ * table; int /*<<< orphan*/  targetsize; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int XT_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xt_tgchk_param*) ; 
 int /*<<< orphan*/  textify_hooks (char*,int,int) ; 
 int /*<<< orphan*/ * xt_prefix ; 

int xt_check_target(struct xt_tgchk_param *par,
		    unsigned int size, u_int8_t proto, bool inv_proto)
{
	if (XT_ALIGN(par->target->targetsize) != size) {
		pr_err("%s_tables: %s target: invalid size %Zu != %u\n",
		       xt_prefix[par->family], par->target->name,
		       XT_ALIGN(par->target->targetsize), size);
		return -EINVAL;
	}
	if (par->target->table != NULL &&
	    strcmp(par->target->table, par->table) != 0) {
		pr_err("%s_tables: %s target: only valid in %s table, not %s\n",
		       xt_prefix[par->family], par->target->name,
		       par->target->table, par->table);
		return -EINVAL;
	}
	if (par->target->hooks && (par->hook_mask & ~par->target->hooks) != 0) {
		char used[64], allow[64];

		pr_err("%s_tables: %s target: used from hooks %s, but only "
		       "usable from %s\n",
		       xt_prefix[par->family], par->target->name,
		       textify_hooks(used, sizeof(used), par->hook_mask),
		       textify_hooks(allow, sizeof(allow), par->target->hooks));
		return -EINVAL;
	}
	if (par->target->proto && (par->target->proto != proto || inv_proto)) {
		pr_err("%s_tables: %s target: only valid for protocol %u\n",
		       xt_prefix[par->family], par->target->name,
		       par->target->proto);
		return -EINVAL;
	}
	if (par->target->checkentry != NULL && !par->target->checkentry(par))
		return -EINVAL;
	return 0;
}