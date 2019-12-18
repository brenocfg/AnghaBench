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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct ocfs2_group_desc {scalar_t__ bg_bitmap; int /*<<< orphan*/  bg_blkno; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int OCFS2_MAX_BACKUP_SUPERBLOCKS ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 scalar_t__ ocfs2_backup_super_blkno (int /*<<< orphan*/ ,int) ; 
 int ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  ocfs2_set_bit (int,unsigned long*) ; 
 scalar_t__ ocfs2_which_cluster_group (struct inode*,int) ; 

__attribute__((used)) static u16 ocfs2_calc_new_backup_super(struct inode *inode,
				       struct ocfs2_group_desc *gd,
				       int new_clusters,
				       u32 first_new_cluster,
				       u16 cl_cpg,
				       int set)
{
	int i;
	u16 backups = 0;
	u32 cluster;
	u64 blkno, gd_blkno, lgd_blkno = le64_to_cpu(gd->bg_blkno);

	for (i = 0; i < OCFS2_MAX_BACKUP_SUPERBLOCKS; i++) {
		blkno = ocfs2_backup_super_blkno(inode->i_sb, i);
		cluster = ocfs2_blocks_to_clusters(inode->i_sb, blkno);

		gd_blkno = ocfs2_which_cluster_group(inode, cluster);
		if (gd_blkno < lgd_blkno)
			continue;
		else if (gd_blkno > lgd_blkno)
			break;

		if (set)
			ocfs2_set_bit(cluster % cl_cpg,
				      (unsigned long *)gd->bg_bitmap);
		else
			ocfs2_clear_bit(cluster % cl_cpg,
					(unsigned long *)gd->bg_bitmap);
		backups++;
	}

	mlog_exit_void();
	return backups;
}