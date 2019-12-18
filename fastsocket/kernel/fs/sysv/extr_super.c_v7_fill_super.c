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
struct v7_super_block {int /*<<< orphan*/  s_time; int /*<<< orphan*/  s_ninode; int /*<<< orphan*/  s_nfree; } ;
struct sysv_sb_info {struct buffer_head* s_bh2; struct buffer_head* s_bh1; int /*<<< orphan*/  s_bytesex; int /*<<< orphan*/  s_type; scalar_t__ s_block_base; struct super_block* s_sb; } ;
struct sysv_inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_mode; } ;
struct super_block {int /*<<< orphan*/  s_id; struct sysv_sb_info* s_fs_info; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTESEX_PDP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSTYPE_V7 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IFDIR ; 
 int V7_NICFREE ; 
 int V7_NICINOD ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ complete_read_super (struct super_block*,int,int) ; 
 int fs16_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 
 int fs32_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sysv_sb_info*) ; 
 struct sysv_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,int) ; 

__attribute__((used)) static int v7_fill_super(struct super_block *sb, void *data, int silent)
{
	struct sysv_sb_info *sbi;
	struct buffer_head *bh, *bh2 = NULL;
	struct v7_super_block *v7sb;
	struct sysv_inode *v7i;

	if (440 != sizeof (struct v7_super_block))
		panic("V7 FS: bad super-block size");
	if (64 != sizeof (struct sysv_inode))
		panic("sysv fs: bad i-node size");

	sbi = kzalloc(sizeof(struct sysv_sb_info), GFP_KERNEL);
	if (!sbi)
		return -ENOMEM;

	sbi->s_sb = sb;
	sbi->s_block_base = 0;
	sbi->s_type = FSTYPE_V7;
	sbi->s_bytesex = BYTESEX_PDP;
	sb->s_fs_info = sbi;
	
	sb_set_blocksize(sb, 512);

	if ((bh = sb_bread(sb, 1)) == NULL) {
		if (!silent)
			printk("VFS: unable to read V7 FS superblock on "
			       "device %s.\n", sb->s_id);
		goto failed;
	}

	/* plausibility check on superblock */
	v7sb = (struct v7_super_block *) bh->b_data;
	if (fs16_to_cpu(sbi, v7sb->s_nfree) > V7_NICFREE ||
	    fs16_to_cpu(sbi, v7sb->s_ninode) > V7_NICINOD ||
	    fs32_to_cpu(sbi, v7sb->s_time) == 0)
		goto failed;

	/* plausibility check on root inode: it is a directory,
	   with a nonzero size that is a multiple of 16 */
	if ((bh2 = sb_bread(sb, 2)) == NULL)
		goto failed;
	v7i = (struct sysv_inode *)(bh2->b_data + 64);
	if ((fs16_to_cpu(sbi, v7i->i_mode) & ~0777) != S_IFDIR ||
	    (fs32_to_cpu(sbi, v7i->i_size) == 0) ||
	    (fs32_to_cpu(sbi, v7i->i_size) & 017) != 0)
		goto failed;
	brelse(bh2);
	bh2 = NULL;

	sbi->s_bh1 = bh;
	sbi->s_bh2 = bh;
	if (complete_read_super(sb, silent, 1))
		return 0;

failed:
	brelse(bh2);
	brelse(bh);
	kfree(sbi);
	return -EINVAL;
}