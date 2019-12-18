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
struct ext4_xattr_entry {int /*<<< orphan*/  e_value_offs; int /*<<< orphan*/  e_value_size; } ;
struct buffer_head {scalar_t__ b_data; int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_refcount; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_file_acl; } ;

/* Variables and functions */
 struct ext4_xattr_entry* BFIRST (struct buffer_head*) ; 
 TYPE_2__* BHDR (struct buffer_head*) ; 
 int EIO ; 
 int ENODATA ; 
 int ERANGE ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ea_idebug (struct inode*,char*,int,...) ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_xattr_cache_insert (struct buffer_head*) ; 
 scalar_t__ ext4_xattr_check_block (struct buffer_head*) ; 
 int ext4_xattr_find_entry (struct ext4_xattr_entry**,int,char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext4_xattr_block_get(struct inode *inode, int name_index, const char *name,
		     void *buffer, size_t buffer_size)
{
	struct buffer_head *bh = NULL;
	struct ext4_xattr_entry *entry;
	size_t size;
	int error;

	ea_idebug(inode, "name=%d.%s, buffer=%p, buffer_size=%ld",
		  name_index, name, buffer, (long)buffer_size);

	error = -ENODATA;
	if (!EXT4_I(inode)->i_file_acl)
		goto cleanup;
	ea_idebug(inode, "reading block %u", EXT4_I(inode)->i_file_acl);
	bh = sb_bread(inode->i_sb, EXT4_I(inode)->i_file_acl);
	if (!bh)
		goto cleanup;
	ea_bdebug(bh, "b_count=%d, refcount=%d",
		atomic_read(&(bh->b_count)), le32_to_cpu(BHDR(bh)->h_refcount));
	if (ext4_xattr_check_block(bh)) {
bad_block:
		ext4_error(inode->i_sb,
			   "inode %lu: bad block %llu", inode->i_ino,
			   EXT4_I(inode)->i_file_acl);
		error = -EIO;
		goto cleanup;
	}
	ext4_xattr_cache_insert(bh);
	entry = BFIRST(bh);
	error = ext4_xattr_find_entry(&entry, name_index, name, bh->b_size, 1);
	if (error == -EIO)
		goto bad_block;
	if (error)
		goto cleanup;
	size = le32_to_cpu(entry->e_value_size);
	if (buffer) {
		error = -ERANGE;
		if (size > buffer_size)
			goto cleanup;
		memcpy(buffer, bh->b_data + le16_to_cpu(entry->e_value_offs),
		       size);
	}
	error = size;

cleanup:
	brelse(bh);
	return error;
}