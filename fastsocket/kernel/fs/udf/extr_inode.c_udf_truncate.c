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
struct TYPE_3__ {scalar_t__ i_data; } ;
struct udf_inode_info {scalar_t__ i_alloc_type; int i_lenAlloc; scalar_t__ i_lenEAttr; TYPE_1__ i_ext; } ;
struct inode {int i_size; TYPE_2__* i_sb; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {int s_blocksize; } ;

/* Variables and functions */
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  block_truncate_page (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fs_time (TYPE_2__*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int /*<<< orphan*/  udf_expand_file_adinicb (struct inode*,int,int*) ; 
 int udf_file_entry_alloc_offset (struct inode*) ; 
 int /*<<< orphan*/  udf_get_block ; 
 int /*<<< orphan*/  udf_sync_inode (struct inode*) ; 
 int /*<<< orphan*/  udf_truncate_extents (struct inode*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

void udf_truncate(struct inode *inode)
{
	int offset;
	int err;
	struct udf_inode_info *iinfo;

	if (!(S_ISREG(inode->i_mode) || S_ISDIR(inode->i_mode) ||
	      S_ISLNK(inode->i_mode)))
		return;
	if (IS_APPEND(inode) || IS_IMMUTABLE(inode))
		return;

	lock_kernel();
	iinfo = UDF_I(inode);
	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) {
		if (inode->i_sb->s_blocksize <
				(udf_file_entry_alloc_offset(inode) +
				 inode->i_size)) {
			udf_expand_file_adinicb(inode, inode->i_size, &err);
			if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) {
				inode->i_size = iinfo->i_lenAlloc;
				unlock_kernel();
				return;
			} else
				udf_truncate_extents(inode);
		} else {
			offset = inode->i_size & (inode->i_sb->s_blocksize - 1);
			memset(iinfo->i_ext.i_data + iinfo->i_lenEAttr + offset,
				0x00, inode->i_sb->s_blocksize -
				offset - udf_file_entry_alloc_offset(inode));
			iinfo->i_lenAlloc = inode->i_size;
		}
	} else {
		block_truncate_page(inode->i_mapping, inode->i_size,
				    udf_get_block);
		udf_truncate_extents(inode);
	}

	inode->i_mtime = inode->i_ctime = current_fs_time(inode->i_sb);
	if (IS_SYNC(inode))
		udf_sync_inode(inode);
	else
		mark_inode_dirty(inode);
	unlock_kernel();
}