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
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {scalar_t__ t_refcount; int /*<<< orphan*/  t_blocks_allocated; struct super_block* t_super; scalar_t__ t_trans_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  j_persistent_trans; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_1__* SB_JOURNAL (struct super_block*) ; 
 int journal_end (struct reiserfs_transaction_handle*,struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct reiserfs_transaction_handle*) ; 

int reiserfs_end_persistent_transaction(struct reiserfs_transaction_handle *th)
{
	struct super_block *s = th->t_super;
	int ret = 0;
	if (th->t_trans_id)
		ret = journal_end(th, th->t_super, th->t_blocks_allocated);
	else
		ret = -EIO;
	if (th->t_refcount == 0) {
		SB_JOURNAL(s)->j_persistent_trans--;
		kfree(th);
	}
	return ret;
}