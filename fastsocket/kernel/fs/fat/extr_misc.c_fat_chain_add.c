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
struct super_block {int dummy; } ;
struct msdos_sb_info {int cluster_bits; } ;
struct inode {int i_blocks; int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct fat_entry {int dummy; } ;
typedef  int /*<<< orphan*/  llu ;
struct TYPE_2__ {int i_start; int i_logstart; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAT_ENT_EOF ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 TYPE_1__* MSDOS_I (struct inode*) ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fat_cache_inval_inode (struct inode*) ; 
 int fat_ent_read (struct inode*,struct fat_entry*,int) ; 
 int fat_ent_write (struct inode*,struct fat_entry*,int,int) ; 
 int /*<<< orphan*/  fat_fs_error (struct super_block*,char*,int,int /*<<< orphan*/ ) ; 
 int fat_get_cluster (struct inode*,int /*<<< orphan*/ ,int*,int*) ; 
 int fat_sync_inode (struct inode*) ; 
 int /*<<< orphan*/  fatent_brelse (struct fat_entry*) ; 
 int /*<<< orphan*/  fatent_init (struct fat_entry*) ; 
 int inode_needs_sync (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

int fat_chain_add(struct inode *inode, int new_dclus, int nr_cluster)
{
	struct super_block *sb = inode->i_sb;
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	int ret, new_fclus, last;

	/*
	 * We must locate the last cluster of the file to add this new
	 * one (new_dclus) to the end of the link list (the FAT).
	 */
	last = new_fclus = 0;
	if (MSDOS_I(inode)->i_start) {
		int fclus, dclus;

		ret = fat_get_cluster(inode, FAT_ENT_EOF, &fclus, &dclus);
		if (ret < 0)
			return ret;
		new_fclus = fclus + 1;
		last = dclus;
	}

	/* add new one to the last of the cluster chain */
	if (last) {
		struct fat_entry fatent;

		fatent_init(&fatent);
		ret = fat_ent_read(inode, &fatent, last);
		if (ret >= 0) {
			int wait = inode_needs_sync(inode);
			ret = fat_ent_write(inode, &fatent, new_dclus, wait);
			fatent_brelse(&fatent);
		}
		if (ret < 0)
			return ret;
//		fat_cache_add(inode, new_fclus, new_dclus);
	} else {
		MSDOS_I(inode)->i_start = new_dclus;
		MSDOS_I(inode)->i_logstart = new_dclus;
		/*
		 * Since generic_write_sync() synchronizes regular files later,
		 * we sync here only directories.
		 */
		if (S_ISDIR(inode->i_mode) && IS_DIRSYNC(inode)) {
			ret = fat_sync_inode(inode);
			if (ret)
				return ret;
		} else
			mark_inode_dirty(inode);
	}
	if (new_fclus != (inode->i_blocks >> (sbi->cluster_bits - 9))) {
		fat_fs_error(sb, "clusters badly computed (%d != %llu)",
			     new_fclus,
			     (llu)(inode->i_blocks >> (sbi->cluster_bits - 9)));
		fat_cache_inval_inode(inode);
	}
	inode->i_blocks += nr_cluster << (sbi->cluster_bits - 9);

	return 0;
}