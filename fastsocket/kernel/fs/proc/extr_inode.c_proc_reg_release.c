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
struct proc_dir_entry {int /*<<< orphan*/  pde_unload_lock; TYPE_1__* proc_fops; int /*<<< orphan*/  pde_users; } ;
struct pde_opener {int (* release ) (struct inode*,struct file*) ;int /*<<< orphan*/  lh; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* release ) (struct inode*,struct file*) ;} ;

/* Variables and functions */
 struct proc_dir_entry* PDE (struct inode*) ; 
 struct pde_opener* find_pde_opener (struct proc_dir_entry*,struct inode*,struct file*) ; 
 int /*<<< orphan*/  kfree (struct pde_opener*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pde_users_dec (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct inode*,struct file*) ; 

__attribute__((used)) static int proc_reg_release(struct inode *inode, struct file *file)
{
	struct proc_dir_entry *pde = PDE(inode);
	int rv = 0;
	int (*release)(struct inode *, struct file *);
	struct pde_opener *pdeo;

	spin_lock(&pde->pde_unload_lock);
	pdeo = find_pde_opener(pde, inode, file);
	if (!pde->proc_fops) {
		/*
		 * Can't simply exit, __fput() will think that everything is OK,
		 * and move on to freeing struct file. remove_proc_entry() will
		 * find slacker in opener's list and will try to do non-trivial
		 * things with struct file. Therefore, remove opener from list.
		 *
		 * But if opener is removed from list, who will ->release it?
		 */
		if (pdeo) {
			list_del(&pdeo->lh);
			spin_unlock(&pde->pde_unload_lock);
			rv = pdeo->release(inode, file);
			kfree(pdeo);
		} else
			spin_unlock(&pde->pde_unload_lock);
		return rv;
	}
	pde->pde_users++;
	release = pde->proc_fops->release;
	if (pdeo) {
		list_del(&pdeo->lh);
		kfree(pdeo);
	}
	spin_unlock(&pde->pde_unload_lock);

	if (release)
		rv = release(inode, file);

	pde_users_dec(pde);
	return rv;
}