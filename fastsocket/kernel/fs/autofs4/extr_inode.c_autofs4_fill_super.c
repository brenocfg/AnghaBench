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
struct inode {int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct file {TYPE_1__* f_op; } ;
struct dentry {struct autofs_sb_info* d_fsdata; int /*<<< orphan*/ * d_op; } ;
struct autofs_sb_info {int pipefd; int catatonic; scalar_t__ version; scalar_t__ min_proto; scalar_t__ max_proto; struct file* pipe; int /*<<< orphan*/  oz_pgrp; scalar_t__ sub_version; int /*<<< orphan*/  type; int /*<<< orphan*/  expiring_list; int /*<<< orphan*/  active_list; int /*<<< orphan*/  lookup_lock; int /*<<< orphan*/ * queues; int /*<<< orphan*/  fs_lock; int /*<<< orphan*/  pipe_mutex; int /*<<< orphan*/  wq_mutex; struct super_block* sb; scalar_t__ exp_timeout; int /*<<< orphan*/  magic; } ;
struct autofs_info {int pipefd; int catatonic; scalar_t__ version; scalar_t__ min_proto; scalar_t__ max_proto; struct file* pipe; int /*<<< orphan*/  oz_pgrp; scalar_t__ sub_version; int /*<<< orphan*/  type; int /*<<< orphan*/  expiring_list; int /*<<< orphan*/  active_list; int /*<<< orphan*/  lookup_lock; int /*<<< orphan*/ * queues; int /*<<< orphan*/  fs_lock; int /*<<< orphan*/  pipe_mutex; int /*<<< orphan*/  wq_mutex; struct super_block* sb; scalar_t__ exp_timeout; int /*<<< orphan*/  magic; } ;
struct TYPE_2__ {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 scalar_t__ AUTOFS_MAX_PROTO_VERSION ; 
 scalar_t__ AUTOFS_MIN_PROTO_VERSION ; 
 scalar_t__ AUTOFS_PROTO_SUBVERSION ; 
 int /*<<< orphan*/  AUTOFS_SBI_MAGIC ; 
 int /*<<< orphan*/  AUTOFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __managed_dentry_set_managed (struct dentry*) ; 
 int /*<<< orphan*/  autofs4_dentry_operations ; 
 int /*<<< orphan*/  autofs4_dir_inode_operations ; 
 struct inode* autofs4_get_inode (struct super_block*,struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs4_mkroot (struct autofs_sb_info*) ; 
 int /*<<< orphan*/  autofs4_root_operations ; 
 int /*<<< orphan*/  autofs4_sops ; 
 scalar_t__ autofs_type_trigger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 struct dentry* d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct autofs_sb_info*) ; 
 struct autofs_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_options (void*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  set_autofs_type_indirect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pgrp_nr (int /*<<< orphan*/ ) ; 

int autofs4_fill_super(struct super_block *s, void *data, int silent)
{
	struct inode * root_inode;
	struct dentry * root;
	struct file * pipe;
	int pipefd;
	struct autofs_sb_info *sbi;
	struct autofs_info *ino;

	sbi = kzalloc(sizeof(*sbi), GFP_KERNEL);
	if (!sbi)
		goto fail_unlock;
	DPRINTK("starting up, sbi = %p",sbi);

	s->s_fs_info = sbi;
	sbi->magic = AUTOFS_SBI_MAGIC;
	sbi->pipefd = -1;
	sbi->pipe = NULL;
	sbi->catatonic = 1;
	sbi->exp_timeout = 0;
	sbi->oz_pgrp = task_pgrp_nr(current);
	sbi->sb = s;
	sbi->version = 0;
	sbi->sub_version = 0;
	set_autofs_type_indirect(&sbi->type);
	sbi->min_proto = 0;
	sbi->max_proto = 0;
	mutex_init(&sbi->wq_mutex);
	mutex_init(&sbi->pipe_mutex);
	spin_lock_init(&sbi->fs_lock);
	sbi->queues = NULL;
	spin_lock_init(&sbi->lookup_lock);
	INIT_LIST_HEAD(&sbi->active_list);
	INIT_LIST_HEAD(&sbi->expiring_list);
	s->s_blocksize = 1024;
	s->s_blocksize_bits = 10;
	s->s_magic = AUTOFS_SUPER_MAGIC;
	s->s_op = &autofs4_sops;
	s->s_time_gran = 1;

	/*
	 * Get the root inode and dentry, but defer checking for errors.
	 */
	ino = autofs4_mkroot(sbi);
	if (!ino)
		goto fail_free;
	root_inode = autofs4_get_inode(s, ino);
	if (!root_inode)
		goto fail_ino;

	root = d_alloc_root(root_inode);
	if (!root)
		goto fail_iput;
	pipe = NULL;

	root->d_op = &autofs4_dentry_operations;
	root->d_fsdata = ino;

	/* Can this call block? */
	if (parse_options(data, &pipefd, &root_inode->i_uid, &root_inode->i_gid,
				&sbi->oz_pgrp, &sbi->type, &sbi->min_proto,
				&sbi->max_proto)) {
		printk("autofs: called with bogus options\n");
		goto fail_dput;
	}

	if (autofs_type_trigger(sbi->type))
		__managed_dentry_set_managed(root);

	root_inode->i_fop = &autofs4_root_operations;
	root_inode->i_op = &autofs4_dir_inode_operations;

	/* Couldn't this be tested earlier? */
	if (sbi->max_proto < AUTOFS_MIN_PROTO_VERSION ||
	    sbi->min_proto > AUTOFS_MAX_PROTO_VERSION) {
		printk("autofs: kernel does not match daemon version "
		       "daemon (%d, %d) kernel (%d, %d)\n",
			sbi->min_proto, sbi->max_proto,
			AUTOFS_MIN_PROTO_VERSION, AUTOFS_MAX_PROTO_VERSION);
		goto fail_dput;
	}

	/* Establish highest kernel protocol version */
	if (sbi->max_proto > AUTOFS_MAX_PROTO_VERSION)
		sbi->version = AUTOFS_MAX_PROTO_VERSION;
	else
		sbi->version = sbi->max_proto;
	sbi->sub_version = AUTOFS_PROTO_SUBVERSION;

	DPRINTK("pipe fd = %d, pgrp = %u", pipefd, sbi->oz_pgrp);
	pipe = fget(pipefd);
	
	if (!pipe) {
		printk("autofs: could not open pipe file descriptor\n");
		goto fail_dput;
	}
	if (!pipe->f_op || !pipe->f_op->write)
		goto fail_fput;
	sbi->pipe = pipe;
	sbi->pipefd = pipefd;
	sbi->catatonic = 0;

	/*
	 * Success! Install the root dentry now to indicate completion.
	 */
	s->s_root = root;
	return 0;
	
	/*
	 * Failure ... clean up.
	 */
fail_fput:
	printk("autofs: pipe file descriptor does not contain proper ops\n");
	fput(pipe);
	/* fall through */
fail_dput:
	dput(root);
	goto fail_free;
fail_iput:
	printk("autofs: get root dentry failed\n");
	iput(root_inode);
fail_ino:
	kfree(ino);
fail_free:
	kfree(sbi);
	s->s_fs_info = NULL;
fail_unlock:
	return -EINVAL;
}