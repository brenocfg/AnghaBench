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
 char* inode_dentry_name (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int rename_file (char*,char*) ; 

int hostfs_rename(struct inode *from_ino, struct dentry *from,
		  struct inode *to_ino, struct dentry *to)
{
	char *from_name, *to_name;
	int err;

	if ((from_name = inode_dentry_name(from_ino, from)) == NULL)
		return -ENOMEM;
	if ((to_name = inode_dentry_name(to_ino, to)) == NULL) {
		kfree(from_name);
		return -ENOMEM;
	}
	err = rename_file(from_name, to_name);
	kfree(from_name);
	kfree(to_name);
	return err;
}