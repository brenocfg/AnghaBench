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
struct sysfs_dirent {int /*<<< orphan*/  s_ino; } ;
struct sysfs_addrm_cxt {struct inode* parent_inode; struct sysfs_dirent* parent_sd; } ;
struct inode {int i_state; int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int I_NEW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct inode* ilookup5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sysfs_dirent*) ; 
 int /*<<< orphan*/  memset (struct sysfs_addrm_cxt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_ilookup_test ; 
 int /*<<< orphan*/  sysfs_mutex ; 
 int /*<<< orphan*/  sysfs_sb ; 

void sysfs_addrm_start(struct sysfs_addrm_cxt *acxt,
		       struct sysfs_dirent *parent_sd)
{
	struct inode *inode;

	memset(acxt, 0, sizeof(*acxt));
	acxt->parent_sd = parent_sd;

	/* Lookup parent inode.  inode initialization is protected by
	 * sysfs_mutex, so inode existence can be determined by
	 * looking up inode while holding sysfs_mutex.
	 */
	mutex_lock(&sysfs_mutex);

	inode = ilookup5(sysfs_sb, parent_sd->s_ino, sysfs_ilookup_test,
			 parent_sd);
	if (inode) {
		WARN_ON(inode->i_state & I_NEW);

		/* parent inode available */
		acxt->parent_inode = inode;

		/* sysfs_mutex is below i_mutex in lock hierarchy.
		 * First, trylock i_mutex.  If fails, unlock
		 * sysfs_mutex and lock them in order.
		 */
		if (!mutex_trylock(&inode->i_mutex)) {
			mutex_unlock(&sysfs_mutex);
			mutex_lock(&inode->i_mutex);
			mutex_lock(&sysfs_mutex);
		}
	}
}