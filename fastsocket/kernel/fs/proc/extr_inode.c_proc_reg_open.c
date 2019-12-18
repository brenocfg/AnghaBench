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
struct proc_dir_entry {int /*<<< orphan*/  pde_unload_lock; int /*<<< orphan*/  pde_openers; TYPE_1__* proc_fops; int /*<<< orphan*/  pde_users; } ;
struct pde_opener {int (* release ) (struct inode*,struct file*) ;int /*<<< orphan*/  lh; struct file* file; struct inode* inode; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* open ) (struct inode*,struct file*) ;int (* release ) (struct inode*,struct file*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct proc_dir_entry* PDE (struct inode*) ; 
 int /*<<< orphan*/  __pde_users_dec (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  kfree (struct pde_opener*) ; 
 struct pde_opener* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proc_reg_open(struct inode *inode, struct file *file)
{
	struct proc_dir_entry *pde = PDE(inode);
	int rv = 0;
	int (*open)(struct inode *, struct file *);
	int (*release)(struct inode *, struct file *);
	struct pde_opener *pdeo;

	/*
	 * What for, you ask? Well, we can have open, rmmod, remove_proc_entry
	 * sequence. ->release won't be called because ->proc_fops will be
	 * cleared. Depending on complexity of ->release, consequences vary.
	 *
	 * We can't wait for mercy when close will be done for real, it's
	 * deadlockable: rmmod foo </proc/foo . So, we're going to do ->release
	 * by hand in remove_proc_entry(). For this, save opener's credentials
	 * for later.
	 */
	pdeo = kmalloc(sizeof(struct pde_opener), GFP_KERNEL);
	if (!pdeo)
		return -ENOMEM;

	spin_lock(&pde->pde_unload_lock);
	if (!pde->proc_fops) {
		spin_unlock(&pde->pde_unload_lock);
		kfree(pdeo);
		return -ENOENT;
	}
	pde->pde_users++;
	open = pde->proc_fops->open;
	release = pde->proc_fops->release;
	spin_unlock(&pde->pde_unload_lock);

	if (open)
		rv = open(inode, file);

	spin_lock(&pde->pde_unload_lock);
	if (rv == 0 && release) {
		/* To know what to release. */
		pdeo->inode = inode;
		pdeo->file = file;
		/* Strictly for "too late" ->release in proc_reg_release(). */
		pdeo->release = release;
		list_add(&pdeo->lh, &pde->pde_openers);
	} else
		kfree(pdeo);
	__pde_users_dec(pde);
	spin_unlock(&pde->pde_unload_lock);
	return rv;
}