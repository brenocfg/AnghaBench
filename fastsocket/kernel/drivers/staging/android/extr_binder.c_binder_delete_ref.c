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
struct TYPE_5__ {int /*<<< orphan*/  entry; } ;
struct binder_ref {struct binder_ref* death; TYPE_2__ work; int /*<<< orphan*/  desc; int /*<<< orphan*/  debug_id; TYPE_1__* proc; TYPE_3__* node; int /*<<< orphan*/  node_entry; scalar_t__ strong; int /*<<< orphan*/  rb_node_node; int /*<<< orphan*/  rb_node_desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  debug_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  refs_by_node; int /*<<< orphan*/  refs_by_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEBUG_DEAD_BINDER ; 
 int /*<<< orphan*/  BINDER_DEBUG_INTERNAL_REFS ; 
 int /*<<< orphan*/  BINDER_STAT_DEATH ; 
 int /*<<< orphan*/  BINDER_STAT_REF ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  binder_dec_node (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  binder_stats_deleted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct binder_ref*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void binder_delete_ref(struct binder_ref *ref)
{
	binder_debug(BINDER_DEBUG_INTERNAL_REFS,
		     "binder: %d delete ref %d desc %d for "
		     "node %d\n", ref->proc->pid, ref->debug_id,
		     ref->desc, ref->node->debug_id);

	rb_erase(&ref->rb_node_desc, &ref->proc->refs_by_desc);
	rb_erase(&ref->rb_node_node, &ref->proc->refs_by_node);
	if (ref->strong)
		binder_dec_node(ref->node, 1, 1);
	hlist_del(&ref->node_entry);
	binder_dec_node(ref->node, 0, 1);
	if (ref->death) {
		binder_debug(BINDER_DEBUG_DEAD_BINDER,
			     "binder: %d delete ref %d desc %d "
			     "has death notification\n", ref->proc->pid,
			     ref->debug_id, ref->desc);
		list_del(&ref->death->work.entry);
		kfree(ref->death);
		binder_stats_deleted(BINDER_STAT_DEATH);
	}
	kfree(ref);
	binder_stats_deleted(BINDER_STAT_REF);
}