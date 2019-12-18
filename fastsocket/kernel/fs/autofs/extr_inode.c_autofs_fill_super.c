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
struct super_block {int s_blocksize; int s_blocksize_bits; int s_time_gran; struct autofs_sb_info* s_fs_info; struct dentry* s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct file {TYPE_1__* f_op; } ;
struct dentry {int dummy; } ;
struct autofs_sb_info {int catatonic; int /*<<< orphan*/  oz_pgrp; struct file* pipe; struct super_block* sb; int /*<<< orphan*/  next_dir_ino; int /*<<< orphan*/  symlink_bitmap; int /*<<< orphan*/ * queues; int /*<<< orphan*/  dirhash; scalar_t__ exp_timeout; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_FIRST_DIR_INO ; 
 int AUTOFS_PROTO_VERSION ; 
 int /*<<< orphan*/  AUTOFS_ROOT_INO ; 
 int /*<<< orphan*/  AUTOFS_SBI_MAGIC ; 
 int /*<<< orphan*/  AUTOFS_SUPER_MAGIC ; 
 int AUTOFS_SYMLINK_BITMAP_LEN ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* autofs_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autofs_initialize_hash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autofs_sops ; 
 struct dentry* d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  find_get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct autofs_sb_info*) ; 
 struct autofs_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_options (void*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_mount_options (struct super_block*,void*) ; 

int autofs_fill_super(struct super_block *s, void *data, int silent)
{
	struct inode * root_inode;
	struct dentry * root;
	struct file * pipe;
	int pipefd;
	struct autofs_sb_info *sbi;
	int minproto, maxproto;
	pid_t pgid;

	save_mount_options(s, data);

	sbi = kzalloc(sizeof(*sbi), GFP_KERNEL);
	if (!sbi)
		goto fail_unlock;
	DPRINTK(("autofs: starting up, sbi = %p\n",sbi));

	s->s_fs_info = sbi;
	sbi->magic = AUTOFS_SBI_MAGIC;
	sbi->pipe = NULL;
	sbi->catatonic = 1;
	sbi->exp_timeout = 0;
	autofs_initialize_hash(&sbi->dirhash);
	sbi->queues = NULL;
	memset(sbi->symlink_bitmap, 0, sizeof(long)*AUTOFS_SYMLINK_BITMAP_LEN);
	sbi->next_dir_ino = AUTOFS_FIRST_DIR_INO;
	s->s_blocksize = 1024;
	s->s_blocksize_bits = 10;
	s->s_magic = AUTOFS_SUPER_MAGIC;
	s->s_op = &autofs_sops;
	s->s_time_gran = 1;
	sbi->sb = s;

	root_inode = autofs_iget(s, AUTOFS_ROOT_INO);
	if (IS_ERR(root_inode))
		goto fail_free;
	root = d_alloc_root(root_inode);
	pipe = NULL;

	if (!root)
		goto fail_iput;

	/* Can this call block?  - WTF cares? s is locked. */
	if (parse_options(data, &pipefd, &root_inode->i_uid,
				&root_inode->i_gid, &pgid, &minproto,
				&maxproto)) {
		printk("autofs: called with bogus options\n");
		goto fail_dput;
	}

	/* Couldn't this be tested earlier? */
	if (minproto > AUTOFS_PROTO_VERSION ||
	     maxproto < AUTOFS_PROTO_VERSION) {
		printk("autofs: kernel does not match daemon version\n");
		goto fail_dput;
	}

	DPRINTK(("autofs: pipe fd = %d, pgrp = %u\n", pipefd, pgid));
	sbi->oz_pgrp = find_get_pid(pgid);

	if (!sbi->oz_pgrp) {
		printk("autofs: could not find process group %d\n", pgid);
		goto fail_dput;
	}

	pipe = fget(pipefd);
	
	if (!pipe) {
		printk("autofs: could not open pipe file descriptor\n");
		goto fail_put_pid;
	}

	if (!pipe->f_op || !pipe->f_op->write)
		goto fail_fput;
	sbi->pipe = pipe;
	sbi->catatonic = 0;

	/*
	 * Success! Install the root dentry now to indicate completion.
	 */
	s->s_root = root;
	return 0;

fail_fput:
	printk("autofs: pipe file descriptor does not contain proper ops\n");
	fput(pipe);
fail_put_pid:
	put_pid(sbi->oz_pgrp);
fail_dput:
	dput(root);
	goto fail_free;
fail_iput:
	printk("autofs: get root dentry failed\n");
	iput(root_inode);
fail_free:
	kfree(sbi);
	s->s_fs_info = NULL;
fail_unlock:
	return -EINVAL;
}