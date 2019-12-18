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
struct xt_mtchk_param {size_t family; int hook_mask; TYPE_1__* match; int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  allow ;
struct TYPE_2__ {int matchsize; int hooks; int /*<<< orphan*/  (* checkentry ) (struct xt_mtchk_param*) ;int /*<<< orphan*/  proto; int /*<<< orphan*/  name; int /*<<< orphan*/ * table; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int XT_ALIGN (int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xt_mtchk_param*) ; 
 int /*<<< orphan*/  textify_hooks (char*,int,int) ; 
 int /*<<< orphan*/ * xt_prefix ; 

int xt_check_match(struct xt_mtchk_param *par,
		   unsigned int size, u_int8_t proto, bool inv_proto)
{
	if (XT_ALIGN(par->match->matchsize) != size &&
	    par->match->matchsize != -1) {
		/*
		 * ebt_among is exempt from centralized matchsize checking
		 * because it uses a dynamic-size data set.
		 */
		pr_err("%s_tables: %s match: invalid size %Zu != %u\n",
		       xt_prefix[par->family], par->match->name,
		       XT_ALIGN(par->match->matchsize), size);
		return -EINVAL;
	}
	if (par->match->table != NULL &&
	    strcmp(par->match->table, par->table) != 0) {
		pr_err("%s_tables: %s match: only valid in %s table, not %s\n",
		       xt_prefix[par->family], par->match->name,
		       par->match->table, par->table);
		return -EINVAL;
	}
	if (par->match->hooks && (par->hook_mask & ~par->match->hooks) != 0) {
		char used[64], allow[64];

		pr_err("%s_tables: %s match: used from hooks %s, but only "
		       "valid from %s\n",
		       xt_prefix[par->family], par->match->name,
		       textify_hooks(used, sizeof(used), par->hook_mask),
		       textify_hooks(allow, sizeof(allow), par->match->hooks));
		return -EINVAL;
	}
	if (par->match->proto && (par->match->proto != proto || inv_proto)) {
		pr_err("%s_tables: %s match: only valid for protocol %u\n",
		       xt_prefix[par->family], par->match->name,
		       par->match->proto);
		return -EINVAL;
	}
	if (par->match->checkentry != NULL && !par->match->checkentry(par))
		return -EINVAL;
	return 0;
}