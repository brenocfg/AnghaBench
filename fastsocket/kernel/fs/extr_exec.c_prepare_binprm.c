#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct linux_binprm {int cred_prepared; int /*<<< orphan*/  buf; TYPE_5__* file; TYPE_4__* cred; int /*<<< orphan*/  per_clear; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct TYPE_8__ {TYPE_2__* mnt; TYPE_1__* dentry; } ;
struct TYPE_10__ {TYPE_3__ f_path; int /*<<< orphan*/ * f_op; } ;
struct TYPE_9__ {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; } ;
struct TYPE_7__ {int mnt_flags; } ;
struct TYPE_6__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINPRM_BUF_SIZE ; 
 int EACCES ; 
 int MNT_NOSUID ; 
 int /*<<< orphan*/  PER_CLEAR_ON_SETID ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int S_IXGRP ; 
 int /*<<< orphan*/  current_egid () ; 
 int /*<<< orphan*/  current_euid () ; 
 int kernel_read (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int security_bprm_set_creds (struct linux_binprm*) ; 

int prepare_binprm(struct linux_binprm *bprm)
{
	umode_t mode;
	struct inode * inode = bprm->file->f_path.dentry->d_inode;
	int retval;

	mode = inode->i_mode;
	if (bprm->file->f_op == NULL)
		return -EACCES;

	/* clear any previous set[ug]id data from a previous binary */
	bprm->cred->euid = current_euid();
	bprm->cred->egid = current_egid();

	if (!(bprm->file->f_path.mnt->mnt_flags & MNT_NOSUID)) {
		/* Set-uid? */
		if (mode & S_ISUID) {
			bprm->per_clear |= PER_CLEAR_ON_SETID;
			bprm->cred->euid = inode->i_uid;
		}

		/* Set-gid? */
		/*
		 * If setgid is set but no group execute bit then this
		 * is a candidate for mandatory locking, not a setgid
		 * executable.
		 */
		if ((mode & (S_ISGID | S_IXGRP)) == (S_ISGID | S_IXGRP)) {
			bprm->per_clear |= PER_CLEAR_ON_SETID;
			bprm->cred->egid = inode->i_gid;
		}
	}

	/* fill in binprm security blob */
	retval = security_bprm_set_creds(bprm);
	if (retval)
		return retval;
	bprm->cred_prepared = 1;

	memset(bprm->buf, 0, BINPRM_BUF_SIZE);
	return kernel_read(bprm->file, 0, bprm->buf, BINPRM_BUF_SIZE);
}