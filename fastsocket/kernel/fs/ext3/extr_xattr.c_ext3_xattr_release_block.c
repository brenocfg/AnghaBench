#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mb_cache_entry {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_bdev; } ;
struct TYPE_8__ {int h_sync; } ;
typedef  TYPE_1__ handle_t ;
struct TYPE_9__ {scalar_t__ h_refcount; } ;

/* Variables and functions */
 TYPE_7__* BHDR (struct buffer_head*) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,...) ; 
 int /*<<< orphan*/  ext3_forget (TYPE_1__*,int,struct inode*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_free_blocks (TYPE_1__*,struct inode*,int /*<<< orphan*/ ,int) ; 
 int ext3_journal_dirty_metadata (TYPE_1__*,struct buffer_head*) ; 
 int ext3_journal_get_write_access (TYPE_1__*,struct buffer_head*) ; 
 int /*<<< orphan*/  ext3_std_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext3_xattr_cache ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  le32_add_cpu (scalar_t__*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mb_cache_entry_free (struct mb_cache_entry*) ; 
 struct mb_cache_entry* mb_cache_entry_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_cache_entry_release (struct mb_cache_entry*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  vfs_dq_free_block (struct inode*,int) ; 

__attribute__((used)) static void
ext3_xattr_release_block(handle_t *handle, struct inode *inode,
			 struct buffer_head *bh)
{
	struct mb_cache_entry *ce = NULL;
	int error = 0;

	ce = mb_cache_entry_get(ext3_xattr_cache, bh->b_bdev, bh->b_blocknr);
	error = ext3_journal_get_write_access(handle, bh);
	if (error)
		 goto out;

	lock_buffer(bh);

	if (BHDR(bh)->h_refcount == cpu_to_le32(1)) {
		ea_bdebug(bh, "refcount now=0; freeing");
		if (ce)
			mb_cache_entry_free(ce);
		ext3_free_blocks(handle, inode, bh->b_blocknr, 1);
		get_bh(bh);
		ext3_forget(handle, 1, inode, bh, bh->b_blocknr);
	} else {
		le32_add_cpu(&BHDR(bh)->h_refcount, -1);
		error = ext3_journal_dirty_metadata(handle, bh);
		if (IS_SYNC(inode))
			handle->h_sync = 1;
		vfs_dq_free_block(inode, 1);
		ea_bdebug(bh, "refcount now=%d; releasing",
			  le32_to_cpu(BHDR(bh)->h_refcount));
		if (ce)
			mb_cache_entry_release(ce);
	}
	unlock_buffer(bh);
out:
	ext3_std_error(inode->i_sb, error);
	return;
}