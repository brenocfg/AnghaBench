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
struct sysv_sb_info {int s_ninodes; int s_fic_size; int s_inodes_per_block_1; } ;
struct sysv_inode {scalar_t__ i_mode; scalar_t__ i_nlink; } ;
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int SYSV_ROOT_INO ; 
 struct sysv_sb_info* SYSV_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_fs16 (struct sysv_sb_info*,int) ; 
 int /*<<< orphan*/ * sv_sb_fic_inode (struct super_block*,int /*<<< orphan*/ ) ; 
 struct sysv_inode* sysv_raw_inode (struct super_block*,int,struct buffer_head**) ; 

__attribute__((used)) static int refill_free_cache(struct super_block *sb)
{
	struct sysv_sb_info *sbi = SYSV_SB(sb);
	struct buffer_head * bh;
	struct sysv_inode * raw_inode;
	int i = 0, ino;

	ino = SYSV_ROOT_INO+1;
	raw_inode = sysv_raw_inode(sb, ino, &bh);
	if (!raw_inode)
		goto out;
	while (ino <= sbi->s_ninodes) {
		if (raw_inode->i_mode == 0 && raw_inode->i_nlink == 0) {
			*sv_sb_fic_inode(sb,i++) = cpu_to_fs16(SYSV_SB(sb), ino);
			if (i == sbi->s_fic_size)
				break;
		}
		if ((ino++ & sbi->s_inodes_per_block_1) == 0) {
			brelse(bh);
			raw_inode = sysv_raw_inode(sb, ino, &bh);
			if (!raw_inode)
				goto out;
		} else
			raw_inode++;
	}
	brelse(bh);
out:
	return i;
}