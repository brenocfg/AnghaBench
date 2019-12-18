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
struct reiserfs_transaction_handle {int t_refcount; int /*<<< orphan*/  t_trans_id; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct reiserfs_transaction_handle* journal_info; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int block_prepare_write (struct page*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  fix_tail_page_for_writing (struct page*) ; 
 int reiserfs_end_persistent_transaction (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  reiserfs_get_block ; 
 scalar_t__ reiserfs_transaction_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_wait_on_write_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (int /*<<< orphan*/ ) ; 

int reiserfs_prepare_write(struct file *f, struct page *page,
			   unsigned from, unsigned to)
{
	struct inode *inode = page->mapping->host;
	int ret;
	int old_ref = 0;

	reiserfs_wait_on_write_block(inode->i_sb);
	fix_tail_page_for_writing(page);
	if (reiserfs_transaction_running(inode->i_sb)) {
		struct reiserfs_transaction_handle *th;
		th = (struct reiserfs_transaction_handle *)current->
		    journal_info;
		BUG_ON(!th->t_refcount);
		BUG_ON(!th->t_trans_id);
		old_ref = th->t_refcount;
		th->t_refcount++;
	}

	ret = block_prepare_write(page, from, to, reiserfs_get_block);
	if (ret && reiserfs_transaction_running(inode->i_sb)) {
		struct reiserfs_transaction_handle *th = current->journal_info;
		/* this gets a little ugly.  If reiserfs_get_block returned an
		 * error and left a transacstion running, we've got to close it,
		 * and we've got to free handle if it was a persistent transaction.
		 *
		 * But, if we had nested into an existing transaction, we need
		 * to just drop the ref count on the handle.
		 *
		 * If old_ref == 0, the transaction is from reiserfs_get_block,
		 * and it was a persistent trans.  Otherwise, it was nested above.
		 */
		if (th->t_refcount > old_ref) {
			if (old_ref)
				th->t_refcount--;
			else {
				int err;
				reiserfs_write_lock(inode->i_sb);
				err = reiserfs_end_persistent_transaction(th);
				reiserfs_write_unlock(inode->i_sb);
				if (err)
					ret = err;
			}
		}
	}
	return ret;

}