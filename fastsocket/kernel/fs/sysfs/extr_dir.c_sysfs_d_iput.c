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
struct inode {int dummy; } ;
struct dentry {struct sysfs_dirent* d_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  sysfs_put (struct sysfs_dirent*) ; 

__attribute__((used)) static void sysfs_d_iput(struct dentry * dentry, struct inode * inode)
{
	struct sysfs_dirent * sd = dentry->d_fsdata;

	sysfs_put(sd);
	iput(inode);
}