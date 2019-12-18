#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xt_tgchk_param {char const* table; unsigned int hook_mask; int /*<<< orphan*/  targinfo; struct xt_target* target; int /*<<< orphan*/  family; struct ebt_entry* entryinfo; } ;
struct xt_target {int /*<<< orphan*/  me; } ;
struct xt_mtchk_param {char const* table; unsigned int hook_mask; int /*<<< orphan*/  family; struct ebt_entry* entryinfo; } ;
struct ebt_table_info {scalar_t__* hook_entry; } ;
struct ebt_standard_target {int /*<<< orphan*/  verdict; } ;
struct TYPE_4__ {struct xt_target* target; int /*<<< orphan*/  name; } ;
struct ebt_entry_target {size_t target_size; int /*<<< orphan*/  data; TYPE_2__ u; } ;
struct ebt_entry {int bitmask; int invflags; int target_offset; size_t next_offset; int /*<<< orphan*/  ethproto; } ;
struct TYPE_3__ {scalar_t__ chaininfo; } ;
struct ebt_cl_stack {unsigned int hookmask; TYPE_1__ cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUGPRINT (char*) ; 
 int EBT_802_3 ; 
 int EBT_F_MASK ; 
 int EBT_INV_MASK ; 
 int EBT_IPROTO ; 
 int EBT_MATCH_ITERATE (struct ebt_entry*,int /*<<< orphan*/ ,...) ; 
 int EBT_NOPROTO ; 
 int EBT_WATCHER_ITERATE (struct ebt_entry*,int /*<<< orphan*/ ,...) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct xt_target*) ; 
 int /*<<< orphan*/  NFPROTO_BRIDGE ; 
 unsigned int NF_BR_NUMHOOKS ; 
 int /*<<< orphan*/  NUM_STANDARD_TARGETS ; 
 int PTR_ERR (struct xt_target*) ; 
 int /*<<< orphan*/  ebt_check_match ; 
 int /*<<< orphan*/  ebt_check_watcher ; 
 int /*<<< orphan*/  ebt_cleanup_match ; 
 int /*<<< orphan*/  ebt_cleanup_watcher ; 
 struct xt_target ebt_standard_target ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct xt_target* try_then_request_module (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int xt_check_target (struct xt_tgchk_param*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xt_find_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ebt_check_entry(struct ebt_entry *e, struct ebt_table_info *newinfo,
   const char *name, unsigned int *cnt,
   struct ebt_cl_stack *cl_s, unsigned int udc_cnt)
{
	struct ebt_entry_target *t;
	struct xt_target *target;
	unsigned int i, j, hook = 0, hookmask = 0;
	size_t gap;
	int ret;
	struct xt_mtchk_param mtpar;
	struct xt_tgchk_param tgpar;

	/* don't mess with the struct ebt_entries */
	if (e->bitmask == 0)
		return 0;

	if (e->bitmask & ~EBT_F_MASK) {
		BUGPRINT("Unknown flag for bitmask\n");
		return -EINVAL;
	}
	if (e->invflags & ~EBT_INV_MASK) {
		BUGPRINT("Unknown flag for inv bitmask\n");
		return -EINVAL;
	}
	if ( (e->bitmask & EBT_NOPROTO) && (e->bitmask & EBT_802_3) ) {
		BUGPRINT("NOPROTO & 802_3 not allowed\n");
		return -EINVAL;
	}
	/* what hook do we belong to? */
	for (i = 0; i < NF_BR_NUMHOOKS; i++) {
		if (!newinfo->hook_entry[i])
			continue;
		if ((char *)newinfo->hook_entry[i] < (char *)e)
			hook = i;
		else
			break;
	}
	/* (1 << NF_BR_NUMHOOKS) tells the check functions the rule is on
	   a base chain */
	if (i < NF_BR_NUMHOOKS)
		hookmask = (1 << hook) | (1 << NF_BR_NUMHOOKS);
	else {
		for (i = 0; i < udc_cnt; i++)
			if ((char *)(cl_s[i].cs.chaininfo) > (char *)e)
				break;
		if (i == 0)
			hookmask = (1 << hook) | (1 << NF_BR_NUMHOOKS);
		else
			hookmask = cl_s[i - 1].hookmask;
	}
	i = 0;

	mtpar.table     = tgpar.table     = name;
	mtpar.entryinfo = tgpar.entryinfo = e;
	mtpar.hook_mask = tgpar.hook_mask = hookmask;
	mtpar.family    = tgpar.family    = NFPROTO_BRIDGE;
	ret = EBT_MATCH_ITERATE(e, ebt_check_match, &mtpar, &i);
	if (ret != 0)
		goto cleanup_matches;
	j = 0;
	ret = EBT_WATCHER_ITERATE(e, ebt_check_watcher, &tgpar, &j);
	if (ret != 0)
		goto cleanup_watchers;
	t = (struct ebt_entry_target *)(((char *)e) + e->target_offset);
	gap = e->next_offset - e->target_offset;

	target = try_then_request_module(
		 xt_find_target(NFPROTO_BRIDGE, t->u.name, 0),
		 "ebt_%s", t->u.name);
	if (IS_ERR(target)) {
		ret = PTR_ERR(target);
		goto cleanup_watchers;
	} else if (target == NULL) {
		ret = -ENOENT;
		goto cleanup_watchers;
	}

	t->u.target = target;
	if (t->u.target == &ebt_standard_target) {
		if (gap < sizeof(struct ebt_standard_target)) {
			BUGPRINT("Standard target size too big\n");
			ret = -EFAULT;
			goto cleanup_watchers;
		}
		if (((struct ebt_standard_target *)t)->verdict <
		   -NUM_STANDARD_TARGETS) {
			BUGPRINT("Invalid standard target\n");
			ret = -EFAULT;
			goto cleanup_watchers;
		}
	} else if (t->target_size > gap - sizeof(struct ebt_entry_target)) {
		module_put(t->u.target->me);
		ret = -EFAULT;
		goto cleanup_watchers;
	}

	tgpar.target   = target;
	tgpar.targinfo = t->data;
	ret = xt_check_target(&tgpar, t->target_size,
	      e->ethproto, e->invflags & EBT_IPROTO);
	if (ret < 0) {
		module_put(target->me);
		goto cleanup_watchers;
	}
	(*cnt)++;
	return 0;
cleanup_watchers:
	EBT_WATCHER_ITERATE(e, ebt_cleanup_watcher, &j);
cleanup_matches:
	EBT_MATCH_ITERATE(e, ebt_cleanup_match, &i);
	return ret;
}