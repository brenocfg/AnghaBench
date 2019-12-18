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
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_refcount; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_file_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFIRST (struct buffer_head*) ; 
 TYPE_2__* BHDR (struct buffer_head*) ; 
 int EIO ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ea_idebug (struct inode*,char*,char*,...) ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_xattr_cache_insert (struct buffer_head*) ; 
 scalar_t__ ext4_xattr_check_block (struct buffer_head*) ; 
 int ext4_xattr_list_entries (struct inode*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext4_xattr_block_list(struct inode *inode, char *buffer, size_t buffer_size)
{
	struct buffer_head *bh = NULL;
	int error;

	ea_idebug(inode, "buffer=%p, buffer_size=%ld",
		  buffer, (long)buffer_size);

	error = 0;
	if (!EXT4_I(inode)->i_file_acl)
		goto cleanup;
	ea_idebug(inode, "reading block %u", EXT4_I(inode)->i_file_acl);
	bh = sb_bread(inode->i_sb, EXT4_I(inode)->i_file_acl);
	error = -EIO;
	if (!bh)
		goto cleanup;
	ea_bdebug(bh, "b_count=%d, refcount=%d",
		atomic_read(&(bh->b_count)), le32_to_cpu(BHDR(bh)->h_refcount));
	if (ext4_xattr_check_block(bh)) {
		ext4_error(inode->i_sb,
			   "inode %lu: bad block %llu", inode->i_ino,
			   EXT4_I(inode)->i_file_acl);
		error = -EIO;
		goto cleanup;
	}
	ext4_xattr_cache_insert(bh);
	error = ext4_xattr_list_entries(inode, BFIRST(bh), buffer, buffer_size);

cleanup:
	brelse(bh);

	return error;
}