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
struct v7_super_block {int /*<<< orphan*/  s_fsize; int /*<<< orphan*/  s_isize; int /*<<< orphan*/  s_time; int /*<<< orphan*/  s_tfree; int /*<<< orphan*/ * s_free; int /*<<< orphan*/  s_nfree; int /*<<< orphan*/  s_tinode; int /*<<< orphan*/ * s_inode; int /*<<< orphan*/  s_ninode; } ;
struct sysv_sb_info {char* s_sbd1; char* s_sbd2; int /*<<< orphan*/  s_nzones; int /*<<< orphan*/  s_firstdatazone; int /*<<< orphan*/ * s_sb_time; int /*<<< orphan*/ * s_free_blocks; int /*<<< orphan*/ * s_bcache; int /*<<< orphan*/ * s_bcache_count; int /*<<< orphan*/ * s_sb_total_free_inodes; int /*<<< orphan*/ * s_sb_fic_inodes; int /*<<< orphan*/ * s_sb_fic_count; int /*<<< orphan*/  s_flc_size; int /*<<< orphan*/  s_fic_size; int /*<<< orphan*/  s_link_max; struct buffer_head* s_bh2; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  V7_LINK_MAX ; 
 int /*<<< orphan*/  V7_NICFREE ; 
 int /*<<< orphan*/  V7_NICINOD ; 
 int /*<<< orphan*/  fs16_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs32_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void detected_v7(struct sysv_sb_info *sbi)
{
	struct buffer_head *bh2 = sbi->s_bh2;
	struct v7_super_block *sbd = (struct v7_super_block *)bh2->b_data;

	sbi->s_link_max = V7_LINK_MAX;
	sbi->s_fic_size = V7_NICINOD;
	sbi->s_flc_size = V7_NICFREE;
	sbi->s_sbd1 = (char *)sbd;
	sbi->s_sbd2 = (char *)sbd;
	sbi->s_sb_fic_count = &sbd->s_ninode;
	sbi->s_sb_fic_inodes = &sbd->s_inode[0];
	sbi->s_sb_total_free_inodes = &sbd->s_tinode;
	sbi->s_bcache_count = &sbd->s_nfree;
	sbi->s_bcache = &sbd->s_free[0];
	sbi->s_free_blocks = &sbd->s_tfree;
	sbi->s_sb_time = &sbd->s_time;
	sbi->s_firstdatazone = fs16_to_cpu(sbi, sbd->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd->s_fsize);
}