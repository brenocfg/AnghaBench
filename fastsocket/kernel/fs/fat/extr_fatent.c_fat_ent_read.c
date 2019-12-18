#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int dummy; } ;
struct msdos_sb_info {int max_cluster; struct fatent_operations* fatent_ops; } ;
struct inode {struct super_block* i_sb; } ;
struct fatent_operations {int (* ent_bread ) (struct super_block*,struct fat_entry*,int,int /*<<< orphan*/ ) ;int (* ent_get ) (struct fat_entry*) ;int /*<<< orphan*/  (* ent_blocknr ) (struct super_block*,int,int*,int /*<<< orphan*/ *) ;} ;
struct fat_entry {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int EIO ; 
 int FAT_START_ENT ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  fat_ent_update_ptr (struct super_block*,struct fat_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fat_fs_error (struct super_block*,char*,int) ; 
 int /*<<< orphan*/  fatent_brelse (struct fat_entry*) ; 
 int /*<<< orphan*/  fatent_set_entry (struct fat_entry*,int) ; 
 int /*<<< orphan*/  stub1 (struct super_block*,int,int*,int /*<<< orphan*/ *) ; 
 int stub2 (struct super_block*,struct fat_entry*,int,int /*<<< orphan*/ ) ; 
 int stub3 (struct fat_entry*) ; 

int fat_ent_read(struct inode *inode, struct fat_entry *fatent, int entry)
{
	struct super_block *sb = inode->i_sb;
	struct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	struct fatent_operations *ops = sbi->fatent_ops;
	int err, offset;
	sector_t blocknr;

	if (entry < FAT_START_ENT || sbi->max_cluster <= entry) {
		fatent_brelse(fatent);
		fat_fs_error(sb, "invalid access to FAT (entry 0x%08x)", entry);
		return -EIO;
	}

	fatent_set_entry(fatent, entry);
	ops->ent_blocknr(sb, entry, &offset, &blocknr);

	if (!fat_ent_update_ptr(sb, fatent, offset, blocknr)) {
		fatent_brelse(fatent);
		err = ops->ent_bread(sb, fatent, offset, blocknr);
		if (err)
			return err;
	}
	return ops->ent_get(fatent);
}