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
struct reiserfs_transaction_handle {int dummy; } ;
struct inode {int i_state; int /*<<< orphan*/  i_sb; scalar_t__ i_blocks; int /*<<< orphan*/  i_data; } ;
struct TYPE_2__ {scalar_t__ k_objectid; } ;

/* Variables and functions */
 TYPE_1__* INODE_PKEY (struct inode*) ; 
 int I_NEW ; 
 int JOURNAL_PER_BALANCE_CNT ; 
 int REISERFS_QUOTA_INIT_BLOCKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 scalar_t__ journal_begin (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ journal_end (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,int) ; 
 int reiserfs_delete_object (struct reiserfs_transaction_handle*,struct inode*) ; 
 int /*<<< orphan*/  reiserfs_delete_xattrs (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_discard_prealloc (struct reiserfs_transaction_handle*,struct inode*) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_save_link (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dq_free_inode (struct inode*) ; 

void reiserfs_delete_inode(struct inode *inode)
{
	/* We need blocks for transaction + (user+group) quota update (possibly delete) */
	int jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 2 +
	    2 * REISERFS_QUOTA_INIT_BLOCKS(inode->i_sb);
	struct reiserfs_transaction_handle th;
	int err;

	truncate_inode_pages(&inode->i_data, 0);

	reiserfs_write_lock(inode->i_sb);

	/* The = 0 happens when we abort creating a new inode for some reason like lack of space.. */
	if (!(inode->i_state & I_NEW) && INODE_PKEY(inode)->k_objectid != 0) {	/* also handles bad_inode case */
		reiserfs_delete_xattrs(inode);

		if (journal_begin(&th, inode->i_sb, jbegin_count))
			goto out;
		reiserfs_update_inode_transaction(inode);

		reiserfs_discard_prealloc(&th, inode);

		err = reiserfs_delete_object(&th, inode);

		/* Do quota update inside a transaction for journaled quotas. We must do that
		 * after delete_object so that quota updates go into the same transaction as
		 * stat data deletion */
		if (!err) 
			vfs_dq_free_inode(inode);

		if (journal_end(&th, inode->i_sb, jbegin_count))
			goto out;

		/* check return value from reiserfs_delete_object after
		 * ending the transaction
		 */
		if (err)
		    goto out;

		/* all items of file are deleted, so we can remove "save" link */
		remove_save_link(inode, 0 /* not truncate */ );	/* we can't do anything
								 * about an error here */
	} else {
		/* no object items are in the tree */
		;
	}
      out:
	clear_inode(inode);	/* note this must go after the journal_end to prevent deadlock */
	inode->i_blocks = 0;
	reiserfs_write_unlock(inode->i_sb);
}