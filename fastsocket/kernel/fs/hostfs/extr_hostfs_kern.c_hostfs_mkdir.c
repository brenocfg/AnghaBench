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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int do_mkdir (char*,int) ; 
 char* inode_dentry_name (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  kfree (char*) ; 

int hostfs_mkdir(struct inode *ino, struct dentry *dentry, int mode)
{
	char *file;
	int err;

	if ((file = inode_dentry_name(ino, dentry)) == NULL)
		return -ENOMEM;
	err = do_mkdir(file, mode);
	kfree(file);
	return err;
}