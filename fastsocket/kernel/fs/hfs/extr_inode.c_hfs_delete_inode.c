#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_dirt; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct TYPE_4__ {scalar_t__ ParID; } ;
struct TYPE_6__ {TYPE_1__ cat_key; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  root_files; int /*<<< orphan*/  file_count; int /*<<< orphan*/  root_dirs; int /*<<< orphan*/  folder_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_INODE ; 
 int /*<<< orphan*/  HFS_FLG_MDB_DIRTY ; 
 TYPE_3__* HFS_I (struct inode*) ; 
 int /*<<< orphan*/  HFS_ROOT_CNID ; 
 TYPE_2__* HFS_SB (struct super_block*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_file_truncate (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hfs_delete_inode(struct inode *inode)
{
	struct super_block *sb = inode->i_sb;

	dprint(DBG_INODE, "delete_inode: %lu\n", inode->i_ino);
	if (S_ISDIR(inode->i_mode)) {
		HFS_SB(sb)->folder_count--;
		if (HFS_I(inode)->cat_key.ParID == cpu_to_be32(HFS_ROOT_CNID))
			HFS_SB(sb)->root_dirs--;
		set_bit(HFS_FLG_MDB_DIRTY, &HFS_SB(sb)->flags);
		sb->s_dirt = 1;
		return;
	}
	HFS_SB(sb)->file_count--;
	if (HFS_I(inode)->cat_key.ParID == cpu_to_be32(HFS_ROOT_CNID))
		HFS_SB(sb)->root_files--;
	if (S_ISREG(inode->i_mode)) {
		if (!inode->i_nlink) {
			inode->i_size = 0;
			hfs_file_truncate(inode);
		}
	}
	set_bit(HFS_FLG_MDB_DIRTY, &HFS_SB(sb)->flags);
	sb->s_dirt = 1;
}