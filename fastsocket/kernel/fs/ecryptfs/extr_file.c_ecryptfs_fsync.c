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
struct file {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecryptfs_dentry_to_lower (struct dentry*) ; 
 int /*<<< orphan*/  ecryptfs_file_to_lower (struct file*) ; 
 int vfs_fsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ecryptfs_fsync(struct file *file, struct dentry *dentry, int datasync)
{
	return vfs_fsync(ecryptfs_file_to_lower(file),
			 ecryptfs_dentry_to_lower(dentry),
			 datasync);
}