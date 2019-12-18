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
typedef  int u8 ;
struct dlm_master_list_entry {scalar_t__ type; int /*<<< orphan*/  wq; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  woken; int /*<<< orphan*/  maybe_map; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DLM_MLE_BLOCK ; 
 int /*<<< orphan*/  O2NM_MAX_NODES ; 
 int /*<<< orphan*/  __dlm_mle_detach_hb_events (struct dlm_ctxt*,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  __dlm_put_mle (struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int find_next_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_clean_block_mle(struct dlm_ctxt *dlm,
				struct dlm_master_list_entry *mle, u8 dead_node)
{
	int bit;

	BUG_ON(mle->type != DLM_MLE_BLOCK);

	spin_lock(&mle->spinlock);
	bit = find_next_bit(mle->maybe_map, O2NM_MAX_NODES, 0);
	if (bit != dead_node) {
		mlog(0, "mle found, but dead node %u would not have been "
		     "master\n", dead_node);
		spin_unlock(&mle->spinlock);
	} else {
		/* Must drop the refcount by one since the assert_master will
		 * never arrive. This may result in the mle being unlinked and
		 * freed, but there may still be a process waiting in the
		 * dlmlock path which is fine. */
		mlog(0, "node %u was expected master\n", dead_node);
		atomic_set(&mle->woken, 1);
		spin_unlock(&mle->spinlock);
		wake_up(&mle->wq);

		/* Do not need events any longer, so detach from heartbeat */
		__dlm_mle_detach_hb_events(dlm, mle);
		__dlm_put_mle(mle);
	}
}