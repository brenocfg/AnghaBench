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
struct the_nilfs {int /*<<< orphan*/  ns_bdev; TYPE_1__* ns_writer; } ;
struct super_block {int dummy; } ;
struct nilfs_transaction_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; struct super_block* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_page; int /*<<< orphan*/  b_bdev; } ;
struct TYPE_4__ {struct the_nilfs* mi_nilfs; } ;
struct TYPE_3__ {struct super_block* s_super; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int EROFS ; 
 TYPE_2__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 scalar_t__ likely (int) ; 
 struct buffer_head* nilfs_grab_buffer (struct inode*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int nilfs_mdt_insert_new_block (struct inode*,unsigned long,struct buffer_head*,void (*) (struct inode*,struct buffer_head*,void*)) ; 
 int /*<<< orphan*/  nilfs_transaction_abort (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_transaction_begin (struct super_block*,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int nilfs_transaction_commit (struct super_block*) ; 
 int /*<<< orphan*/  page_cache_release (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

__attribute__((used)) static int nilfs_mdt_create_block(struct inode *inode, unsigned long block,
				  struct buffer_head **out_bh,
				  void (*init_block)(struct inode *,
						     struct buffer_head *,
						     void *))
{
	struct the_nilfs *nilfs = NILFS_MDT(inode)->mi_nilfs;
	struct super_block *sb = inode->i_sb;
	struct nilfs_transaction_info ti;
	struct buffer_head *bh;
	int err;

	if (!sb) {
		/*
		 * Make sure this function is not called from any
		 * read-only context.
		 */
		if (!nilfs->ns_writer) {
			WARN_ON(1);
			err = -EROFS;
			goto out;
		}
		sb = nilfs->ns_writer->s_super;
	}

	nilfs_transaction_begin(sb, &ti, 0);

	err = -ENOMEM;
	bh = nilfs_grab_buffer(inode, inode->i_mapping, block, 0);
	if (unlikely(!bh))
		goto failed_unlock;

	err = -EEXIST;
	if (buffer_uptodate(bh))
		goto failed_bh;

	wait_on_buffer(bh);
	if (buffer_uptodate(bh))
		goto failed_bh;

	bh->b_bdev = nilfs->ns_bdev;
	err = nilfs_mdt_insert_new_block(inode, block, bh, init_block);
	if (likely(!err)) {
		get_bh(bh);
		*out_bh = bh;
	}

 failed_bh:
	unlock_page(bh->b_page);
	page_cache_release(bh->b_page);
	brelse(bh);

 failed_unlock:
	if (likely(!err))
		err = nilfs_transaction_commit(sb);
	else
		nilfs_transaction_abort(sb);
 out:
	return err;
}