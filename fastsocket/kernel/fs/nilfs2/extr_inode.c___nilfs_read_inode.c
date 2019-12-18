#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct nilfs_sb_info {int /*<<< orphan*/  s_ifile; int /*<<< orphan*/  s_nilfs; } ;
struct nilfs_inode {int /*<<< orphan*/  i_device_code; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/ * i_op; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mi_sem; } ;
struct TYPE_3__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 TYPE_2__* NILFS_MDT (struct inode*) ; 
 struct nilfs_sb_info* NILFS_SB (struct super_block*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_decode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_aops ; 
 struct inode* nilfs_dat_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_dir_inode_operations ; 
 int /*<<< orphan*/  nilfs_dir_operations ; 
 int /*<<< orphan*/  nilfs_file_inode_operations ; 
 int /*<<< orphan*/  nilfs_file_operations ; 
 int nilfs_ifile_get_inode_block (int /*<<< orphan*/ ,unsigned long,struct buffer_head**) ; 
 struct nilfs_inode* nilfs_ifile_map_inode (int /*<<< orphan*/ ,unsigned long,struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_ifile_unmap_inode (int /*<<< orphan*/ ,unsigned long,struct buffer_head*) ; 
 int nilfs_read_inode_common (struct inode*,struct nilfs_inode*) ; 
 int /*<<< orphan*/  nilfs_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  nilfs_special_inode_operations ; 
 int /*<<< orphan*/  nilfs_symlink_inode_operations ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __nilfs_read_inode(struct super_block *sb, unsigned long ino,
			      struct inode *inode)
{
	struct nilfs_sb_info *sbi = NILFS_SB(sb);
	struct inode *dat = nilfs_dat_inode(sbi->s_nilfs);
	struct buffer_head *bh;
	struct nilfs_inode *raw_inode;
	int err;

	down_read(&NILFS_MDT(dat)->mi_sem);	/* XXX */
	err = nilfs_ifile_get_inode_block(sbi->s_ifile, ino, &bh);
	if (unlikely(err))
		goto bad_inode;

	raw_inode = nilfs_ifile_map_inode(sbi->s_ifile, ino, bh);

	err = nilfs_read_inode_common(inode, raw_inode);
	if (err)
		goto failed_unmap;

	if (S_ISREG(inode->i_mode)) {
		inode->i_op = &nilfs_file_inode_operations;
		inode->i_fop = &nilfs_file_operations;
		inode->i_mapping->a_ops = &nilfs_aops;
	} else if (S_ISDIR(inode->i_mode)) {
		inode->i_op = &nilfs_dir_inode_operations;
		inode->i_fop = &nilfs_dir_operations;
		inode->i_mapping->a_ops = &nilfs_aops;
	} else if (S_ISLNK(inode->i_mode)) {
		inode->i_op = &nilfs_symlink_inode_operations;
		inode->i_mapping->a_ops = &nilfs_aops;
	} else {
		inode->i_op = &nilfs_special_inode_operations;
		init_special_inode(
			inode, inode->i_mode,
			new_decode_dev(le64_to_cpu(raw_inode->i_device_code)));
	}
	nilfs_ifile_unmap_inode(sbi->s_ifile, ino, bh);
	brelse(bh);
	up_read(&NILFS_MDT(dat)->mi_sem);	/* XXX */
	nilfs_set_inode_flags(inode);
	return 0;

 failed_unmap:
	nilfs_ifile_unmap_inode(sbi->s_ifile, ino, bh);
	brelse(bh);

 bad_inode:
	up_read(&NILFS_MDT(dat)->mi_sem);	/* XXX */
	return err;
}