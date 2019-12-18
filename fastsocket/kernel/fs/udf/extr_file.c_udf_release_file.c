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
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_discard_prealloc (struct inode*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int udf_release_file(struct inode *inode, struct file *filp)
{
	if (filp->f_mode & FMODE_WRITE) {
		mutex_lock(&inode->i_mutex);
		lock_kernel();
		udf_discard_prealloc(inode);
		unlock_kernel();
		mutex_unlock(&inode->i_mutex);
	}
	return 0;
}