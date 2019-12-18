#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_sb; } ;
struct ext3_xattr_info {int name_index; char const* name; void const* value; size_t value_len; } ;
struct TYPE_20__ {int /*<<< orphan*/ * bh; } ;
struct TYPE_18__ {scalar_t__ not_found; } ;
struct ext3_xattr_ibody_find {TYPE_8__ iloc; TYPE_2__ s; } ;
struct TYPE_17__ {int /*<<< orphan*/  base; scalar_t__ not_found; } ;
struct ext3_xattr_block_find {int /*<<< orphan*/ * bh; TYPE_1__ s; } ;
struct ext3_inode {int dummy; } ;
struct TYPE_19__ {int h_sync; } ;
typedef  TYPE_3__ handle_t ;
struct TYPE_16__ {int i_state; int /*<<< orphan*/  xattr_sem; scalar_t__ i_file_acl; } ;
struct TYPE_15__ {int /*<<< orphan*/  s_inode_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENOSPC ; 
 int ERANGE ; 
 TYPE_14__* EXT3_I (struct inode*) ; 
 TYPE_13__* EXT3_SB (int /*<<< orphan*/ ) ; 
 int EXT3_STATE_NEW ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int XATTR_CREATE ; 
 int XATTR_REPLACE ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int ext3_get_inode_loc (struct inode*,TYPE_8__*) ; 
 int ext3_journal_get_write_access (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ext3_mark_iloc_dirty (TYPE_3__*,struct inode*,TYPE_8__*) ; 
 struct ext3_inode* ext3_raw_inode (TYPE_8__*) ; 
 int ext3_xattr_block_find (struct inode*,struct ext3_xattr_info*,struct ext3_xattr_block_find*) ; 
 int ext3_xattr_block_set (TYPE_3__*,struct inode*,struct ext3_xattr_info*,struct ext3_xattr_block_find*) ; 
 int ext3_xattr_ibody_find (struct inode*,struct ext3_xattr_info*,struct ext3_xattr_ibody_find*) ; 
 int ext3_xattr_ibody_set (TYPE_3__*,struct inode*,struct ext3_xattr_info*,struct ext3_xattr_ibody_find*) ; 
 int /*<<< orphan*/  ext3_xattr_update_super_block (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ext3_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int
ext3_xattr_set_handle(handle_t *handle, struct inode *inode, int name_index,
		      const char *name, const void *value, size_t value_len,
		      int flags)
{
	struct ext3_xattr_info i = {
		.name_index = name_index,
		.name = name,
		.value = value,
		.value_len = value_len,

	};
	struct ext3_xattr_ibody_find is = {
		.s = { .not_found = -ENODATA, },
	};
	struct ext3_xattr_block_find bs = {
		.s = { .not_found = -ENODATA, },
	};
	int error;

	if (!name)
		return -EINVAL;
	if (strlen(name) > 255)
		return -ERANGE;
	down_write(&EXT3_I(inode)->xattr_sem);
	error = ext3_get_inode_loc(inode, &is.iloc);
	if (error)
		goto cleanup;

	error = ext3_journal_get_write_access(handle, is.iloc.bh);
	if (error)
		goto cleanup;

	if (EXT3_I(inode)->i_state & EXT3_STATE_NEW) {
		struct ext3_inode *raw_inode = ext3_raw_inode(&is.iloc);
		memset(raw_inode, 0, EXT3_SB(inode->i_sb)->s_inode_size);
		EXT3_I(inode)->i_state &= ~EXT3_STATE_NEW;
	}

	error = ext3_xattr_ibody_find(inode, &i, &is);
	if (error)
		goto cleanup;
	if (is.s.not_found)
		error = ext3_xattr_block_find(inode, &i, &bs);
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
			error = ext3_xattr_ibody_set(handle, inode, &i, &is);
		else if (!bs.s.not_found)
			error = ext3_xattr_block_set(handle, inode, &i, &bs);
	} else {
		error = ext3_xattr_ibody_set(handle, inode, &i, &is);
		if (!error && !bs.s.not_found) {
			i.value = NULL;
			error = ext3_xattr_block_set(handle, inode, &i, &bs);
		} else if (error == -ENOSPC) {
			if (EXT3_I(inode)->i_file_acl && !bs.s.base) {
				error = ext3_xattr_block_find(inode, &i, &bs);
				if (error)
					goto cleanup;
			}
			error = ext3_xattr_block_set(handle, inode, &i, &bs);
			if (error)
				goto cleanup;
			if (!is.s.not_found) {
				i.value = NULL;
				error = ext3_xattr_ibody_set(handle, inode, &i,
							     &is);
			}
		}
	}
	if (!error) {
		ext3_xattr_update_super_block(handle, inode->i_sb);
		inode->i_ctime = CURRENT_TIME_SEC;
		error = ext3_mark_iloc_dirty(handle, inode, &is.iloc);
		/*
		 * The bh is consumed by ext3_mark_iloc_dirty, even with
		 * error != 0.
		 */
		is.iloc.bh = NULL;
		if (IS_SYNC(inode))
			handle->h_sync = 1;
	}

cleanup:
	brelse(is.iloc.bh);
	brelse(bs.bh);
	up_write(&EXT3_I(inode)->xattr_sem);
	return error;
}