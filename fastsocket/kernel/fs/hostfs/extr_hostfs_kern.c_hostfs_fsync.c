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
struct file {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 TYPE_1__* HOSTFS_I (int /*<<< orphan*/ ) ; 
 int fsync_file (int /*<<< orphan*/ ,int) ; 

int hostfs_fsync(struct file *file, struct dentry *dentry, int datasync)
{
	return fsync_file(HOSTFS_I(dentry->d_inode)->fd, datasync);
}