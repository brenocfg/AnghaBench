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
struct super_block {int s_dirt; } ;
struct msdos_sb_info {int free_clusters; int free_clus_valid; int prev_free; int max_cluster; struct fatent_operations* fatent_ops; } ;
struct inode {struct super_block* i_sb; } ;
struct fatent_operations {scalar_t__ (* ent_get ) (struct fat_entry*) ;int /*<<< orphan*/  (* ent_put ) (struct fat_entry*,int) ;} ;
struct fat_entry {int entry; scalar_t__ nr_bhs; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSPC ; 
 int FAT_ENT_EOF ; 
 scalar_t__ FAT_ENT_FREE ; 
 void* FAT_START_ENT ; 
 int MAX_BUF_PER_PAGE ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  fat_collect_bhs (struct buffer_head**,int*,struct fat_entry*) ; 
 scalar_t__ fat_ent_next (struct msdos_sb_info*,struct fat_entry*) ; 
 int fat_ent_read_block (struct super_block*,struct fat_entry*) ; 
 int /*<<< orphan*/  fat_free_clusters (struct inode*,int) ; 
 int fat_mirror_bhs (struct super_block*,struct buffer_head**,int) ; 
 int fat_sync_bhs (struct buffer_head**,int) ; 
 int /*<<< orphan*/  fatent_brelse (struct fat_entry*) ; 
 int /*<<< orphan*/  fatent_init (struct fat_entry*) ; 
 int /*<<< orphan*/  fatent_set_entry (struct fat_entry*,int) ; 
 scalar_t__ inode_needs_sync (struct inode*) ; 
 int /*<<< orphan*/  lock_fat (struct msdos_sb_info*) ; 
 scalar_t__ stub1 (struct fat_entry*) ; 
 int /*<<< orphan*/  stub2 (struct fat_entry*,int) ; 
 int /*<<< orphan*/  stub3 (struct fat_entry*,int) ; 
 int /*<<< orphan*/  unlock_fat (struct msdos_sb_info*) ; 

int fat_alloc_clusters(struct inode *inode, int *cluster, int nr_cluster)
{
	struct super_block *sb = inode->i_sb;
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	struct fatent_operations *ops = sbi->fatent_ops;
	struct fat_entry fatent, prev_ent;
	struct buffer_head *bhs[MAX_BUF_PER_PAGE];
	int i, count, err, nr_bhs, idx_clus;

	BUG_ON(nr_cluster > (MAX_BUF_PER_PAGE / 2));	/* fixed limit */

	lock_fat(sbi);
	if (sbi->free_clusters != -1 && sbi->free_clus_valid &&
	    sbi->free_clusters < nr_cluster) {
		unlock_fat(sbi);
		return -ENOSPC;
	}

	err = nr_bhs = idx_clus = 0;
	count = FAT_START_ENT;
	fatent_init(&prev_ent);
	fatent_init(&fatent);
	fatent_set_entry(&fatent, sbi->prev_free + 1);
	while (count < sbi->max_cluster) {
		if (fatent.entry >= sbi->max_cluster)
			fatent.entry = FAT_START_ENT;
		fatent_set_entry(&fatent, fatent.entry);
		err = fat_ent_read_block(sb, &fatent);
		if (err)
			goto out;

		/* Find the free entries in a block */
		do {
			if (ops->ent_get(&fatent) == FAT_ENT_FREE) {
				int entry = fatent.entry;

				/* make the cluster chain */
				ops->ent_put(&fatent, FAT_ENT_EOF);
				if (prev_ent.nr_bhs)
					ops->ent_put(&prev_ent, entry);

				fat_collect_bhs(bhs, &nr_bhs, &fatent);

				sbi->prev_free = entry;
				if (sbi->free_clusters != -1)
					sbi->free_clusters--;
				sb->s_dirt = 1;

				cluster[idx_clus] = entry;
				idx_clus++;
				if (idx_clus == nr_cluster)
					goto out;

				/*
				 * fat_collect_bhs() gets ref-count of bhs,
				 * so we can still use the prev_ent.
				 */
				prev_ent = fatent;
			}
			count++;
			if (count == sbi->max_cluster)
				break;
		} while (fat_ent_next(sbi, &fatent));
	}

	/* Couldn't allocate the free entries */
	sbi->free_clusters = 0;
	sbi->free_clus_valid = 1;
	sb->s_dirt = 1;
	err = -ENOSPC;

out:
	unlock_fat(sbi);
	fatent_brelse(&fatent);
	if (!err) {
		if (inode_needs_sync(inode))
			err = fat_sync_bhs(bhs, nr_bhs);
		if (!err)
			err = fat_mirror_bhs(sb, bhs, nr_bhs);
	}
	for (i = 0; i < nr_bhs; i++)
		brelse(bhs[i]);

	if (err && idx_clus)
		fat_free_clusters(inode, cluster[0]);

	return err;
}