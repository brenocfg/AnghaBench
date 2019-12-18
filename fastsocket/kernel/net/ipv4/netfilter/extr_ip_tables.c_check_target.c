#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xt_tgchk_param {char const* table; int /*<<< orphan*/  family; int /*<<< orphan*/  hook_mask; int /*<<< orphan*/  targinfo; TYPE_3__* target; struct ipt_entry* entryinfo; } ;
struct TYPE_8__ {TYPE_3__* target; } ;
struct TYPE_6__ {TYPE_4__ kernel; scalar_t__ target_size; } ;
struct ipt_entry_target {TYPE_2__ u; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int invflags; int /*<<< orphan*/  proto; } ;
struct ipt_entry {TYPE_1__ ip; int /*<<< orphan*/  comefrom; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IPT_INV_PROTO ; 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  duprintf (char*,int /*<<< orphan*/ ) ; 
 struct ipt_entry_target* ipt_get_target (struct ipt_entry*) ; 
 int xt_check_target (struct xt_tgchk_param*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_target(struct ipt_entry *e, const char *name)
{
	struct ipt_entry_target *t = ipt_get_target(e);
	struct xt_tgchk_param par = {
		.table     = name,
		.entryinfo = e,
		.target    = t->u.kernel.target,
		.targinfo  = t->data,
		.hook_mask = e->comefrom,
		.family    = NFPROTO_IPV4,
	};
	int ret;

	ret = xt_check_target(&par, t->u.target_size - sizeof(*t),
	      e->ip.proto, e->ip.invflags & IPT_INV_PROTO);
	if (ret < 0) {
		duprintf("ip_tables: check failed for `%s'.\n",
			 t->u.kernel.target->name);
		return ret;
	}
	return 0;
}