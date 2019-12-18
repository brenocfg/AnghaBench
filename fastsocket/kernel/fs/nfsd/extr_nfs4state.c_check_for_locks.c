#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nfs4_stateowner {int dummy; } ;
struct nfs4_file {struct inode* fi_inode; } ;
struct inode {struct file_lock* i_flock; } ;
struct file_lock {scalar_t__ fl_owner; struct file_lock* fl_next; } ;
typedef  scalar_t__ fl_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
check_for_locks(struct nfs4_file *filp, struct nfs4_stateowner *lowner)
{
	struct file_lock **flpp;
	struct inode *inode = filp->fi_inode;
	int status = 0;

	lock_kernel();
	for (flpp = &inode->i_flock; *flpp != NULL; flpp = &(*flpp)->fl_next) {
		if ((*flpp)->fl_owner == (fl_owner_t)lowner) {
			status = 1;
			goto out;
		}
	}
out:
	unlock_kernel();
	return status;
}