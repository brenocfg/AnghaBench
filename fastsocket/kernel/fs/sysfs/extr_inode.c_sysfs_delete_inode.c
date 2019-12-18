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
struct sysfs_dirent {int dummy; } ;
struct inode {int /*<<< orphan*/  i_data; struct sysfs_dirent* i_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  sysfs_put (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sysfs_delete_inode(struct inode *inode)
{
	struct sysfs_dirent *sd  = inode->i_private;

	truncate_inode_pages(&inode->i_data, 0);
	clear_inode(inode);
	sysfs_put(sd);
}