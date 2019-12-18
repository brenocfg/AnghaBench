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
 char* dentry_name (struct dentry*,int /*<<< orphan*/ ) ; 
 char* inode_dentry_name (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int link_file (char*,char*) ; 

int hostfs_link(struct dentry *to, struct inode *ino, struct dentry *from)
{
	char *from_name, *to_name;
	int err;

	if ((from_name = inode_dentry_name(ino, from)) == NULL)
		return -ENOMEM;
	to_name = dentry_name(to, 0);
	if (to_name == NULL) {
		kfree(from_name);
		return -ENOMEM;
	}
	err = link_file(to_name, from_name);
	kfree(from_name);
	kfree(to_name);
	return err;
}