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
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_5__ {int /*<<< orphan*/  d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* llseek ) (struct file*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct proc_dir_entry* PDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_llseek (struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pde_users_dec (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static loff_t proc_reg_llseek(struct file *file, loff_t offset, int whence)
{
	struct proc_dir_entry *pde = PDE(file->f_path.dentry->d_inode);
	loff_t rv = -EINVAL;
	loff_t (*llseek)(struct file *, loff_t, int);

	spin_lock(&pde->pde_unload_lock);
	/*
	 * remove_proc_entry() is going to delete PDE (as part of module
	 * cleanup sequence). No new callers into module allowed.
	 */
	if (!pde->proc_fops) {
		spin_unlock(&pde->pde_unload_lock);
		return rv;
	}
	/*
	 * Bump refcount so that remove_proc_entry will wail for ->llseek to
	 * complete.
	 */
	pde->pde_users++;
	/*
	 * Save function pointer under lock, to protect against ->proc_fops
	 * NULL'ifying right after ->pde_unload_lock is dropped.
	 */
	llseek = pde->proc_fops->llseek;
	spin_unlock(&pde->pde_unload_lock);

	if (!llseek)
		llseek = default_llseek;
	rv = llseek(file, offset, whence);

	pde_users_dec(pde);
	return rv;
}