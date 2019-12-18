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
struct xt_tgchk_param {char* table; unsigned int hook_mask; int /*<<< orphan*/  family; int /*<<< orphan*/  targinfo; struct xt_target* target; int /*<<< orphan*/ * entryinfo; } ;
struct xt_target {int /*<<< orphan*/  me; } ;
struct TYPE_5__ {struct xt_target* target; } ;
struct TYPE_4__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__ kernel; scalar_t__ target_size; TYPE_1__ user; } ;
struct ipt_entry_target {TYPE_3__ u; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ENOENT ; 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int xt_check_target (struct xt_tgchk_param*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct xt_target* xt_request_find_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipt_init_target(struct ipt_entry_target *t, char *table, unsigned int hook)
{
	struct xt_tgchk_param par;
	struct xt_target *target;
	int ret = 0;

	target = xt_request_find_target(AF_INET, t->u.user.name,
					t->u.user.revision);
	if (!target)
		return -ENOENT;

	t->u.kernel.target = target;
	par.table     = table;
	par.entryinfo = NULL;
	par.target    = target;
	par.targinfo  = t->data;
	par.hook_mask = hook;
	par.family    = NFPROTO_IPV4;

	ret = xt_check_target(&par, t->u.target_size - sizeof(*t), 0, false);
	if (ret < 0) {
		module_put(t->u.kernel.target->me);
		return ret;
	}
	return 0;
}