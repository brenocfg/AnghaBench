#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct proc_dir_entry {int /*<<< orphan*/  pde_unload_lock; TYPE_1__* proc_fops; int /*<<< orphan*/  pde_users; } ;
struct TYPE_6__ {TYPE_2__* dentry; } ;
struct file {TYPE_3__ f_path; } ;
struct TYPE_5__ {struct inode* d_inode; } ;
struct TYPE_4__ {long (* unlocked_ioctl ) (struct file*,unsigned int,unsigned long) ;int (* ioctl ) (struct inode*,struct file*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 long EINVAL ; 
 long ENOIOCTLCMD ; 
 long ENOTTY ; 
 struct proc_dir_entry* PDE (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  pde_users_dec (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static long proc_reg_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct proc_dir_entry *pde = PDE(file->f_path.dentry->d_inode);
	long rv = -ENOTTY;
	long (*unlocked_ioctl)(struct file *, unsigned int, unsigned long);
	int (*ioctl)(struct inode *, struct file *, unsigned int, unsigned long);

	spin_lock(&pde->pde_unload_lock);
	if (!pde->proc_fops) {
		spin_unlock(&pde->pde_unload_lock);
		return rv;
	}
	pde->pde_users++;
	unlocked_ioctl = pde->proc_fops->unlocked_ioctl;
	ioctl = pde->proc_fops->ioctl;
	spin_unlock(&pde->pde_unload_lock);

	if (unlocked_ioctl) {
		rv = unlocked_ioctl(file, cmd, arg);
		if (rv == -ENOIOCTLCMD)
			rv = -EINVAL;
	} else if (ioctl) {
		lock_kernel();
		rv = ioctl(file->f_path.dentry->d_inode, file, cmd, arg);
		unlock_kernel();
	}

	pde_users_dec(pde);
	return rv;
}