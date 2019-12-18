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
typedef  scalar_t__ time_t ;
struct reiserfs_transaction_handle {int t_refcount; int t_blocks_allocated; int /*<<< orphan*/  t_trans_id; int /*<<< orphan*/  t_super; } ;
struct reiserfs_journal {scalar_t__ j_must_wait; scalar_t__ j_len_alloc; scalar_t__ j_max_batch; scalar_t__ j_trans_start_time; scalar_t__ j_max_trans_age; int j_cnode_free; int j_trans_max; int /*<<< orphan*/  j_jlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct reiserfs_journal* SB_JOURNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ get_seconds () ; 

int journal_transaction_should_end(struct reiserfs_transaction_handle *th,
				   int new_alloc)
{
	struct reiserfs_journal *journal = SB_JOURNAL(th->t_super);
	time_t now = get_seconds();
	/* cannot restart while nested */
	BUG_ON(!th->t_trans_id);
	if (th->t_refcount > 1)
		return 0;
	if (journal->j_must_wait > 0 ||
	    (journal->j_len_alloc + new_alloc) >= journal->j_max_batch ||
	    atomic_read(&(journal->j_jlock)) ||
	    (now - journal->j_trans_start_time) > journal->j_max_trans_age ||
	    journal->j_cnode_free < (journal->j_trans_max * 3)) {
		return 1;
	}
	/* protected by the BKL here */
	journal->j_len_alloc += new_alloc;
	th->t_blocks_allocated += new_alloc ;
	return 0;
}