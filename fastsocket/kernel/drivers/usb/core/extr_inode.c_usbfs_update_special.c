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
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 TYPE_1__* devices_usbfs_dentry ; 

void usbfs_update_special (void)
{
	struct inode *inode;

	if (devices_usbfs_dentry) {
		inode = devices_usbfs_dentry->d_inode;
		if (inode)
			inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
	}
}