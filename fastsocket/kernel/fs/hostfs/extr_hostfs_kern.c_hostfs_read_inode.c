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
struct inode {int /*<<< orphan*/  i_dentry; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (char*) ; 
 scalar_t__ OS_TYPE_SYMLINK ; 
 int PTR_ERR (char*) ; 
 scalar_t__ file_type (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* follow_link (char*) ; 
 char* inode_name (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int read_name (struct inode*,char*) ; 

__attribute__((used)) static int hostfs_read_inode(struct inode *ino)
{
	char *name;
	int err = 0;

	/*
	 * Unfortunately, we are called from iget() when we don't have a dentry
	 * allocated yet.
	 */
	if (list_empty(&ino->i_dentry))
		goto out;

	err = -ENOMEM;
	name = inode_name(ino, 0);
	if (name == NULL)
		goto out;

	if (file_type(name, NULL, NULL) == OS_TYPE_SYMLINK) {
		name = follow_link(name);
		if (IS_ERR(name)) {
			err = PTR_ERR(name);
			goto out;
		}
	}

	err = read_name(ino, name);
	kfree(name);
 out:
	return err;
}