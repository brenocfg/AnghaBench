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
struct super_block {struct qnx4_sb_info* s_fs_info; int /*<<< orphan*/ * s_root; int /*<<< orphan*/  s_flags; scalar_t__ s_magic; int /*<<< orphan*/ * s_op; } ;
struct qnx4_super_block {int dummy; } ;
struct qnx4_sb_info {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {struct qnx4_super_block* sb; struct buffer_head* sb_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  MS_RDONLY ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  QNX4_BLOCK_SIZE ; 
 int QNX4_INODES_PER_BLOCK ; 
 int QNX4_ROOT_INO ; 
 scalar_t__ QNX4_SUPER_MAGIC ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/ * d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct qnx4_sb_info*) ; 
 struct qnx4_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 char* qnx4_checkroot (struct super_block*) ; 
 struct inode* qnx4_iget (struct super_block*,int) ; 
 TYPE_1__* qnx4_sb (struct super_block*) ; 
 int /*<<< orphan*/  qnx4_sops ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qnx4_fill_super(struct super_block *s, void *data, int silent)
{
	struct buffer_head *bh;
	struct inode *root;
	const char *errmsg;
	struct qnx4_sb_info *qs;
	int ret = -EINVAL;

	qs = kzalloc(sizeof(struct qnx4_sb_info), GFP_KERNEL);
	if (!qs)
		return -ENOMEM;
	s->s_fs_info = qs;

	sb_set_blocksize(s, QNX4_BLOCK_SIZE);

	/* Check the superblock signature. Since the qnx4 code is
	   dangerous, we should leave as quickly as possible
	   if we don't belong here... */
	bh = sb_bread(s, 1);
	if (!bh) {
		printk("qnx4: unable to read the superblock\n");
		goto outnobh;
	}
	if ( le32_to_cpup((__le32*) bh->b_data) != QNX4_SUPER_MAGIC ) {
		if (!silent)
			printk("qnx4: wrong fsid in superblock.\n");
		goto out;
	}
	s->s_op = &qnx4_sops;
	s->s_magic = QNX4_SUPER_MAGIC;
	s->s_flags |= MS_RDONLY;	/* Yup, read-only yet */
	qnx4_sb(s)->sb_buf = bh;
	qnx4_sb(s)->sb = (struct qnx4_super_block *) bh->b_data;


 	/* check before allocating dentries, inodes, .. */
	errmsg = qnx4_checkroot(s);
	if (errmsg != NULL) {
 		if (!silent)
 			printk("qnx4: %s\n", errmsg);
		goto out;
	}

 	/* does root not have inode number QNX4_ROOT_INO ?? */
	root = qnx4_iget(s, QNX4_ROOT_INO * QNX4_INODES_PER_BLOCK);
	if (IS_ERR(root)) {
 		printk("qnx4: get inode failed\n");
		ret = PTR_ERR(root);
 		goto out;
 	}

	ret = -ENOMEM;
 	s->s_root = d_alloc_root(root);
 	if (s->s_root == NULL)
 		goto outi;

	brelse(bh);

	return 0;

      outi:
	iput(root);
      out:
	brelse(bh);
      outnobh:
	kfree(qs);
	s->s_fs_info = NULL;
	return ret;
}