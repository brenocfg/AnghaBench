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
struct xt_tgdtor_param {TYPE_2__* target; int /*<<< orphan*/  family; int /*<<< orphan*/  targinfo; } ;
struct TYPE_3__ {TYPE_2__* target; } ;
struct ebt_entry_target {int /*<<< orphan*/  data; TYPE_1__ u; } ;
struct ebt_entry {scalar_t__ bitmask; int target_offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  me; int /*<<< orphan*/  (* destroy ) (struct xt_tgdtor_param*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EBT_MATCH_ITERATE (struct ebt_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EBT_WATCHER_ITERATE (struct ebt_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFPROTO_BRIDGE ; 
 int /*<<< orphan*/  ebt_cleanup_match ; 
 int /*<<< orphan*/  ebt_cleanup_watcher ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xt_tgdtor_param*) ; 

__attribute__((used)) static inline int
ebt_cleanup_entry(struct ebt_entry *e, unsigned int *cnt)
{
	struct xt_tgdtor_param par;
	struct ebt_entry_target *t;

	if (e->bitmask == 0)
		return 0;
	/* we're done */
	if (cnt && (*cnt)-- == 0)
		return 1;
	EBT_WATCHER_ITERATE(e, ebt_cleanup_watcher, NULL);
	EBT_MATCH_ITERATE(e, ebt_cleanup_match, NULL);
	t = (struct ebt_entry_target *)(((char *)e) + e->target_offset);

	par.target   = t->u.target;
	par.targinfo = t->data;
	par.family   = NFPROTO_BRIDGE;
	if (par.target->destroy != NULL)
		par.target->destroy(&par);
	module_put(par.target->me);
	return 0;
}