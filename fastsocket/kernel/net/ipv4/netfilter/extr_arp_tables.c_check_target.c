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
struct xt_tgchk_param {char const* table; int /*<<< orphan*/  family; int /*<<< orphan*/  hook_mask; int /*<<< orphan*/  targinfo; TYPE_1__* target; struct arpt_entry* entryinfo; } ;
struct TYPE_5__ {TYPE_1__* target; } ;
struct TYPE_6__ {TYPE_2__ kernel; scalar_t__ target_size; } ;
struct arpt_entry_target {TYPE_3__ u; int /*<<< orphan*/  data; } ;
struct arpt_entry {int /*<<< orphan*/  comefrom; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_ARP ; 
 struct arpt_entry_target* arpt_get_target (struct arpt_entry*) ; 
 int /*<<< orphan*/  duprintf (char*,int /*<<< orphan*/ ) ; 
 int xt_check_target (struct xt_tgchk_param*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int check_target(struct arpt_entry *e, const char *name)
{
	struct arpt_entry_target *t = arpt_get_target(e);
	int ret;
	struct xt_tgchk_param par = {
		.table     = name,
		.entryinfo = e,
		.target    = t->u.kernel.target,
		.targinfo  = t->data,
		.hook_mask = e->comefrom,
		.family    = NFPROTO_ARP,
	};

	ret = xt_check_target(&par, t->u.target_size - sizeof(*t), 0, false);
	if (ret < 0) {
		duprintf("arp_tables: check failed for `%s'.\n",
			 t->u.kernel.target->name);
		return ret;
	}
	return 0;
}