#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct pid_namespace {struct bsd_acct_struct* bacct; } ;
struct TYPE_8__ {struct vfsmount* mnt; TYPE_2__* dentry; } ;
struct file {TYPE_4__ f_path; TYPE_3__* f_op; } ;
struct bsd_acct_struct {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  write; } ;
struct TYPE_6__ {TYPE_1__* d_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int EACCES ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int O_APPEND ; 
 int O_LARGEFILE ; 
 int O_WRONLY ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acct_file_reopen (struct bsd_acct_struct*,struct file*,struct pid_namespace*) ; 
 int /*<<< orphan*/  acct_lock ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  filp_close (struct file*,int /*<<< orphan*/ *) ; 
 struct file* filp_open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bsd_acct_struct*) ; 
 struct bsd_acct_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_pin (struct vfsmount*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int security_acct (struct file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct pid_namespace* task_active_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acct_on(const char *name)
{
	struct file *file;
	struct vfsmount *mnt;
	int error;
	struct pid_namespace *ns;
	struct bsd_acct_struct *acct = NULL;

	/* Difference from BSD - they don't do O_APPEND */
	file = filp_open(name, O_WRONLY|O_APPEND|O_LARGEFILE, 0);
	if (IS_ERR(file))
		return PTR_ERR(file);

	if (!S_ISREG(file->f_path.dentry->d_inode->i_mode)) {
		filp_close(file, NULL);
		return -EACCES;
	}

	if (!file->f_op->write) {
		filp_close(file, NULL);
		return -EIO;
	}

	ns = task_active_pid_ns(current);
	if (ns->bacct == NULL) {
		acct = kzalloc(sizeof(struct bsd_acct_struct), GFP_KERNEL);
		if (acct == NULL) {
			filp_close(file, NULL);
			return -ENOMEM;
		}
	}

	error = security_acct(file);
	if (error) {
		kfree(acct);
		filp_close(file, NULL);
		return error;
	}

	spin_lock(&acct_lock);
	if (ns->bacct == NULL) {
		ns->bacct = acct;
		acct = NULL;
	}

	mnt = file->f_path.mnt;
	mnt_pin(mnt);
	acct_file_reopen(ns->bacct, file, ns);
	spin_unlock(&acct_lock);

	mntput(mnt); /* it's pinned, now give up active reference */
	kfree(acct);

	return 0;
}