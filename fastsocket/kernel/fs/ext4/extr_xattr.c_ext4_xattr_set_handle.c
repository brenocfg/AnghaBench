#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_sb; } ;
struct ext4_xattr_info {int name_index; char const* name; void const* value; size_t value_len; } ;
struct TYPE_10__ {int /*<<< orphan*/ * bh; } ;
struct TYPE_9__ {scalar_t__ not_found; } ;
struct ext4_xattr_ibody_find {TYPE_3__ iloc; TYPE_2__ s; } ;
struct TYPE_8__ {int /*<<< orphan*/  base; scalar_t__ not_found; } ;
struct ext4_xattr_block_find {int /*<<< orphan*/ * bh; TYPE_1__ s; } ;
struct ext4_inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_12__ {int /*<<< orphan*/  xattr_sem; scalar_t__ i_file_acl; } ;
struct TYPE_11__ {int /*<<< orphan*/  s_inode_size; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENOSPC ; 
 int ERANGE ; 
 TYPE_7__* EXT4_I (struct inode*) ; 
 TYPE_6__* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_STATE_NEW ; 
 int /*<<< orphan*/  EXT4_STATE_NO_EXPAND ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int XATTR_CREATE ; 
 int XATTR_REPLACE ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_current_time (struct inode*) ; 
 int ext4_get_inode_loc (struct inode*,TYPE_3__*) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ext4_mark_iloc_dirty (int /*<<< orphan*/ *,struct inode*,TYPE_3__*) ; 
 struct ext4_inode* ext4_raw_inode (TYPE_3__*) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 long ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_xattr_block_find (struct inode*,struct ext4_xattr_info*,struct ext4_xattr_block_find*) ; 
 int ext4_xattr_block_set (int /*<<< orphan*/ *,struct inode*,struct ext4_xattr_info*,struct ext4_xattr_block_find*) ; 
 int ext4_xattr_ibody_find (struct inode*,struct ext4_xattr_info*,struct ext4_xattr_ibody_find*) ; 
 int ext4_xattr_ibody_set (int /*<<< orphan*/ *,struct inode*,struct ext4_xattr_info*,struct ext4_xattr_ibody_find*) ; 
 int /*<<< orphan*/  ext4_xattr_update_super_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ext4_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int
ext4_xattr_set_handle(handle_t *handle, struct inode *inode, int name_index,
		      const char *name, const void *value, size_t value_len,
		      int flags)
{
	struct ext4_xattr_info i = {
		.name_index = name_index,
		.name = name,
		.value = value,
		.value_len = value_len,

	};
	struct ext4_xattr_ibody_find is = {
		.s = { .not_found = -ENODATA, },
	};
	struct ext4_xattr_block_find bs = {
		.s = { .not_found = -ENODATA, },
	};
	unsigned long no_expand;
	int error;

	if (!name)
		return -EINVAL;
	if (strlen(name) > 255)
		return -ERANGE;
	down_write(&EXT4_I(inode)->xattr_sem);
	no_expand = ext4_test_inode_state(inode, EXT4_STATE_NO_EXPAND);
	ext4_set_inode_state(inode, EXT4_STATE_NO_EXPAND);

	error = ext4_get_inode_loc(inode, &is.iloc);
	if (error)
		goto cleanup;

	error = ext4_journal_get_write_access(handle, is.iloc.bh);
	if (error)
		goto cleanup;

	if (ext4_test_inode_state(inode, EXT4_STATE_NEW)) {
		struct ext4_inode *raw_inode = ext4_raw_inode(&is.iloc);
		memset(raw_inode, 0, EXT4_SB(inode->i_sb)->s_inode_size);
		ext4_clear_inode_state(inode, EXT4_STATE_NEW);
	}

	error = ext4_xattr_ibody_find(inode, &i, &is);
	if (error)
		goto cleanup;
	if (is.s.not_found)
		error = ext4_xattr_block_find(inode, &i, &bs);
	if (error)
		goto cleanup;
	if (is.s.not_found && bs.s.not_found) {
		error = -ENODATA;
		if (flags & XATTR_REPLACE)
			goto cleanup;
		error = 0;
		if (!value)
			goto cleanup;
	} else {
		error = -EEXIST;
		if (flags & XATTR_CREATE)
			goto cleanup;
	}
	if (!value) {
		if (!is.s.not_found)
			error = ext4_xattr_ibody_set(handle, inode, &i, &is);
		else if (!bs.s.not_found)
			error = ext4_xattr_block_set(handle, inode, &i, &bs);
	} else {
		error = ext4_xattr_ibody_set(handle, inode, &i, &is);
		if (!error && !bs.s.not_found) {
			i.value = NULL;
			error = ext4_xattr_block_set(handle, inode, &i, &bs);
		} else if (error == -ENOSPC) {
			if (EXT4_I(inode)->i_file_acl && !bs.s.base) {
				error = ext4_xattr_block_find(inode, &i, &bs);
				if (error)
					goto cleanup;
			}
			error = ext4_xattr_block_set(handle, inode, &i, &bs);
			if (error)
				goto cleanup;
			if (!is.s.not_found) {
				i.value = NULL;
				error = ext4_xattr_ibody_set(handle, inode, &i,
							     &is);
			}
		}
	}
	if (!error) {
		ext4_xattr_update_super_block(handle, inode->i_sb);
		inode->i_ctime = ext4_current_time(inode);
		if (!value)
			ext4_clear_inode_state(inode, EXT4_STATE_NO_EXPAND);
		error = ext4_mark_iloc_dirty(handle, inode, &is.iloc);
		/*
		 * The bh is consumed by ext4_mark_iloc_dirty, even with
		 * error != 0.
		 */
		is.iloc.bh = NULL;
		if (IS_SYNC(inode))
			ext4_handle_sync(handle);
	}

cleanup:
	brelse(is.iloc.bh);
	brelse(bs.bh);
	if (no_expand == 0)
		ext4_clear_inode_state(inode, EXT4_STATE_NO_EXPAND);
	up_write(&EXT4_I(inode)->xattr_sem);
	return error;
}