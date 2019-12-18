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
struct nilfs_sb_info {int /*<<< orphan*/  s_next_gen_lock; int /*<<< orphan*/  s_next_generation; int /*<<< orphan*/  s_inodes_count; int /*<<< orphan*/  s_ifile; } ;
struct nilfs_inode_info {int i_state; int i_flags; scalar_t__ i_cno; scalar_t__ i_dir_start_lookup; int /*<<< orphan*/  i_bmap; int /*<<< orphan*/  i_bh; } ;
struct inode {int i_mode; scalar_t__ i_nlink; scalar_t__ i_generation; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mapping; struct super_block* i_sb; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int NILFS_APPEND_FL ; 
 int NILFS_DIRSYNC_FL ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int NILFS_IMMUTABLE_FL ; 
 int /*<<< orphan*/  NILFS_I_BMAP ; 
 int NILFS_I_NEW ; 
 struct nilfs_sb_info* NILFS_SB (struct super_block*) ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 int __GFP_FS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int mapping_gfp_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int nilfs_bmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nilfs_ifile_create_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nilfs_init_acl (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  nilfs_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

struct inode *nilfs_new_inode(struct inode *dir, int mode)
{
	struct super_block *sb = dir->i_sb;
	struct nilfs_sb_info *sbi = NILFS_SB(sb);
	struct inode *inode;
	struct nilfs_inode_info *ii;
	int err = -ENOMEM;
	ino_t ino;

	inode = new_inode(sb);
	if (unlikely(!inode))
		goto failed;

	mapping_set_gfp_mask(inode->i_mapping,
			     mapping_gfp_mask(inode->i_mapping) & ~__GFP_FS);

	ii = NILFS_I(inode);
	ii->i_state = 1 << NILFS_I_NEW;

	err = nilfs_ifile_create_inode(sbi->s_ifile, &ino, &ii->i_bh);
	if (unlikely(err))
		goto failed_ifile_create_inode;
	/* reference count of i_bh inherits from nilfs_mdt_read_block() */

	atomic_inc(&sbi->s_inodes_count);

	inode->i_uid = current_fsuid();
	if (dir->i_mode & S_ISGID) {
		inode->i_gid = dir->i_gid;
		if (S_ISDIR(mode))
			mode |= S_ISGID;
	} else
		inode->i_gid = current_fsgid();

	inode->i_mode = mode;
	inode->i_ino = ino;
	inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME;

	if (S_ISREG(mode) || S_ISDIR(mode) || S_ISLNK(mode)) {
		err = nilfs_bmap_read(ii->i_bmap, NULL);
		if (err < 0)
			goto failed_bmap;

		set_bit(NILFS_I_BMAP, &ii->i_state);
		/* No lock is needed; iget() ensures it. */
	}

	ii->i_flags = NILFS_I(dir)->i_flags;
	if (S_ISLNK(mode))
		ii->i_flags &= ~(NILFS_IMMUTABLE_FL | NILFS_APPEND_FL);
	if (!S_ISDIR(mode))
		ii->i_flags &= ~NILFS_DIRSYNC_FL;

	/* ii->i_file_acl = 0; */
	/* ii->i_dir_acl = 0; */
	ii->i_dir_start_lookup = 0;
	ii->i_cno = 0;
	nilfs_set_inode_flags(inode);
	spin_lock(&sbi->s_next_gen_lock);
	inode->i_generation = sbi->s_next_generation++;
	spin_unlock(&sbi->s_next_gen_lock);
	insert_inode_hash(inode);

	err = nilfs_init_acl(inode, dir);
	if (unlikely(err))
		goto failed_acl; /* never occur. When supporting
				    nilfs_init_acl(), proper cancellation of
				    above jobs should be considered */

	mark_inode_dirty(inode);
	return inode;

 failed_acl:
 failed_bmap:
	inode->i_nlink = 0;
	iput(inode);  /* raw_inode will be deleted through
			 generic_delete_inode() */
	goto failed;

 failed_ifile_create_inode:
	make_bad_inode(inode);
	iput(inode);  /* if i_nlink == 1, generic_forget_inode() will be
			 called */
 failed:
	return ERR_PTR(err);
}