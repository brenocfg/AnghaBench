#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_size; int /*<<< orphan*/  i_mutex; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {int f_pos; TYPE_2__ f_path; } ;
typedef  int loff_t ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static loff_t
proc_bus_pci_lseek(struct file *file, loff_t off, int whence)
{
	loff_t new = -1;
	struct inode *inode = file->f_path.dentry->d_inode;

	mutex_lock(&inode->i_mutex);
	switch (whence) {
	case 0:
		new = off;
		break;
	case 1:
		new = file->f_pos + off;
		break;
	case 2:
		new = inode->i_size + off;
		break;
	}
	if (new < 0 || new > inode->i_size)
		new = -EINVAL;
	else
		file->f_pos = new;
	mutex_unlock(&inode->i_mutex);
	return new;
}