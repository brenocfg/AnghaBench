#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {struct autofs_info* d_fsdata; int /*<<< orphan*/  d_parent; int /*<<< orphan*/ * d_op; TYPE_1__ d_name; } ;
struct autofs_sb_info {int /*<<< orphan*/  type; int /*<<< orphan*/  catatonic; } ;
struct autofs_info {struct dentry* dentry; } ;
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ROOT (int /*<<< orphan*/ ) ; 
 scalar_t__ NAME_MAX ; 
 int /*<<< orphan*/  __managed_dentry_set_managed (struct dentry*) ; 
 int /*<<< orphan*/  autofs4_add_active (struct dentry*) ; 
 int /*<<< orphan*/  autofs4_dentry_operations ; 
 struct autofs_info* autofs4_init_ino (int /*<<< orphan*/ *,struct autofs_sb_info*,int) ; 
 struct dentry* autofs4_lookup_active (struct dentry*) ; 
 int /*<<< orphan*/  autofs4_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 scalar_t__ autofs_type_indirect (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pgrp_nr (TYPE_2__*) ; 

__attribute__((used)) static struct dentry *autofs4_lookup(struct inode *dir, struct dentry *dentry, struct nameidata *nd)
{
	struct autofs_sb_info *sbi;
	struct autofs_info *ino;
	struct dentry *active;

	DPRINTK("name = %.*s", dentry->d_name.len, dentry->d_name.name);

	/* File name too long to exist */
	if (dentry->d_name.len > NAME_MAX)
		return ERR_PTR(-ENAMETOOLONG);

	sbi = autofs4_sbi(dir->i_sb);

	DPRINTK("pid = %u, pgrp = %u, catatonic = %d",
		 current->pid, task_pgrp_nr(current), sbi->catatonic);

	active = autofs4_lookup_active(dentry);
	if (active)
		return active;
	else {
		dentry->d_op = &autofs4_dentry_operations;

		/*
		 * A dentry that is not within the root can never trigger
		 * a mount operation, so we can return fail immediately.
		 * The daemon however does need to create directories
		 * within the file system.
		 */
		if (!autofs4_oz_mode(sbi) && !IS_ROOT(dentry->d_parent))
			return ERR_PTR(-ENOENT);

		/* Mark entries in the root as mount triggers */
		if (autofs_type_indirect(sbi->type) && IS_ROOT(dentry->d_parent))
			__managed_dentry_set_managed(dentry);

		ino = autofs4_init_ino(NULL, sbi, 0555);
		if (!ino)
			return ERR_PTR(-ENOMEM);

		dentry->d_fsdata = ino;
		ino->dentry = dentry;

		autofs4_add_active(dentry);

		d_instantiate(dentry, NULL);
	}

	return NULL;
}