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
struct udf_sb_info {int /*<<< orphan*/  s_alloc_mutex; scalar_t__ s_lvid_bh; } ;
struct super_block {int dummy; } ;
struct logicalVolIntegrityDescImpUse {int /*<<< orphan*/  numFiles; int /*<<< orphan*/  numDirs; } ;
struct inode {int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_location; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_1__* UDF_I (struct inode*) ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_free_blocks (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct logicalVolIntegrityDescImpUse* udf_sb_lvidiu (struct udf_sb_info*) ; 
 int /*<<< orphan*/  udf_updated_lvid (struct super_block*) ; 
 int /*<<< orphan*/  vfs_dq_drop (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_free_inode (struct inode*) ; 

void udf_free_inode(struct inode *inode)
{
	struct super_block *sb = inode->i_sb;
	struct udf_sb_info *sbi = UDF_SB(sb);

	/*
	 * Note: we must free any quota before locking the superblock,
	 * as writing the quota to disk may need the lock as well.
	 */
	vfs_dq_free_inode(inode);
	vfs_dq_drop(inode);

	clear_inode(inode);

	mutex_lock(&sbi->s_alloc_mutex);
	if (sbi->s_lvid_bh) {
		struct logicalVolIntegrityDescImpUse *lvidiu =
							udf_sb_lvidiu(sbi);
		if (S_ISDIR(inode->i_mode))
			le32_add_cpu(&lvidiu->numDirs, -1);
		else
			le32_add_cpu(&lvidiu->numFiles, -1);
		udf_updated_lvid(sb);
	}
	mutex_unlock(&sbi->s_alloc_mutex);

	udf_free_blocks(sb, NULL, &UDF_I(inode)->i_location, 0, 1);
}