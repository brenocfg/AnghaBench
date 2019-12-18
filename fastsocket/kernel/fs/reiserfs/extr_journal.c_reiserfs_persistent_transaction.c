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
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {int t_refcount; } ;
struct TYPE_4__ {int /*<<< orphan*/  j_persistent_trans; } ;
struct TYPE_3__ {struct reiserfs_transaction_handle* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 TYPE_2__* SB_JOURNAL (struct super_block*) ; 
 TYPE_1__* current ; 
 int journal_begin (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int /*<<< orphan*/  kfree (struct reiserfs_transaction_handle*) ; 
 struct reiserfs_transaction_handle* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ reiserfs_transaction_running (struct super_block*) ; 

struct reiserfs_transaction_handle *reiserfs_persistent_transaction(struct
								    super_block
								    *s,
								    int nblocks)
{
	int ret;
	struct reiserfs_transaction_handle *th;

	/* if we're nesting into an existing transaction.  It will be
	 ** persistent on its own
	 */
	if (reiserfs_transaction_running(s)) {
		th = current->journal_info;
		th->t_refcount++;
		BUG_ON(th->t_refcount < 2);
		
		return th;
	}
	th = kmalloc(sizeof(struct reiserfs_transaction_handle), GFP_NOFS);
	if (!th)
		return NULL;
	ret = journal_begin(th, s, nblocks);
	if (ret) {
		kfree(th);
		return NULL;
	}

	SB_JOURNAL(s)->j_persistent_trans++;
	return th;
}