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
struct msdos_sb_info {int cluster_bits; } ;
struct inode {int i_size; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {scalar_t__ i_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAT_ENT_EOF ; 
 TYPE_1__* MSDOS_I (struct inode*) ; 
 struct msdos_sb_info* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int fat_get_cluster (struct inode*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int fat_calc_dir_size(struct inode *inode)
{
	struct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	int ret, fclus, dclus;

	inode->i_size = 0;
	if (MSDOS_I(inode)->i_start == 0)
		return 0;

	ret = fat_get_cluster(inode, FAT_ENT_EOF, &fclus, &dclus);
	if (ret < 0)
		return ret;
	inode->i_size = (fclus + 1) << sbi->cluster_bits;

	return 0;
}