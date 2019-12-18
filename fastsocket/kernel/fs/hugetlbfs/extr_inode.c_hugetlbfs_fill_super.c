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
struct super_block {int s_time_gran; struct dentry* s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_maxbytes; struct hugetlbfs_sb_info* s_fs_info; } ;
struct inode {int dummy; } ;
struct hugetlbfs_sb_info {int max_inodes; int free_inodes; struct hugetlbfs_sb_info* spool; int /*<<< orphan*/  stat_lock; int /*<<< orphan*/ * hstate; } ;
struct hugetlbfs_config {int nr_blocks; int nr_inodes; int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/ * hstate; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HUGETLBFS_MAGIC ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 struct dentry* d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  default_hstate ; 
 int /*<<< orphan*/  huge_page_shift (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_page_size (int /*<<< orphan*/ *) ; 
 struct hugetlbfs_sb_info* hugepage_new_subpool (int) ; 
 struct inode* hugetlbfs_get_inode (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugetlbfs_ops ; 
 int hugetlbfs_parse_options (void*,struct hugetlbfs_config*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct hugetlbfs_sb_info*) ; 
 struct hugetlbfs_sb_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_mount_options (struct super_block*,void*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hugetlbfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct inode * inode;
	struct dentry * root;
	int ret;
	struct hugetlbfs_config config;
	struct hugetlbfs_sb_info *sbinfo;

	save_mount_options(sb, data);

	config.nr_blocks = -1; /* No limit on size by default */
	config.nr_inodes = -1; /* No limit on number of inodes by default */
	config.uid = current_fsuid();
	config.gid = current_fsgid();
	config.mode = 0755;
	config.hstate = &default_hstate;
	ret = hugetlbfs_parse_options(data, &config);
	if (ret)
		return ret;

	sbinfo = kmalloc(sizeof(struct hugetlbfs_sb_info), GFP_KERNEL);
	if (!sbinfo)
		return -ENOMEM;
	sb->s_fs_info = sbinfo;
	sbinfo->hstate = config.hstate;
	spin_lock_init(&sbinfo->stat_lock);
	sbinfo->max_inodes = config.nr_inodes;
	sbinfo->free_inodes = config.nr_inodes;
	sbinfo->spool = NULL;
	if (config.nr_blocks != -1) {
		sbinfo->spool = hugepage_new_subpool(config.nr_blocks);
		if (!sbinfo->spool)
			goto out_free;
	}
	sb->s_maxbytes = MAX_LFS_FILESIZE;
	sb->s_blocksize = huge_page_size(config.hstate);
	sb->s_blocksize_bits = huge_page_shift(config.hstate);
	sb->s_magic = HUGETLBFS_MAGIC;
	sb->s_op = &hugetlbfs_ops;
	sb->s_time_gran = 1;
	inode = hugetlbfs_get_inode(sb, config.uid, config.gid,
					S_IFDIR | config.mode, 0);
	if (!inode)
		goto out_free;

	root = d_alloc_root(inode);
	if (!root) {
		iput(inode);
		goto out_free;
	}
	sb->s_root = root;
	return 0;
out_free:
	if (sbinfo->spool)
		kfree(sbinfo->spool);
	kfree(sbinfo);
	return -ENOMEM;
}