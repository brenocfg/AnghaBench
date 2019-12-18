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
struct throtl_grp {int limits_changed; int* bps; int* iops; int /*<<< orphan*/  ref; int /*<<< orphan*/ * bio_lists; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  tg_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void throtl_init_group(struct throtl_grp *tg)
{
	INIT_HLIST_NODE(&tg->tg_node);
	RB_CLEAR_NODE(&tg->rb_node);
	bio_list_init(&tg->bio_lists[0]);
	bio_list_init(&tg->bio_lists[1]);
	tg->limits_changed = false;

	/* Practically unlimited BW */
	tg->bps[0] = tg->bps[1] = -1;
	tg->iops[0] = tg->iops[1] = -1;

	/*
	 * Take the initial reference that will be released on destroy
	 * This can be thought of a joint reference by cgroup and
	 * request queue which will be dropped by either request queue
	 * exit or cgroup deletion path depending on who is exiting first.
	 */
	atomic_set(&tg->ref, 1);
}