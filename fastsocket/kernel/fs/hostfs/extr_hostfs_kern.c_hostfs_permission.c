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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAY_EXEC ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int access_file (char*,int,int,int) ; 
 int generic_permission (struct inode*,int,int /*<<< orphan*/ *) ; 
 char* inode_name (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 

int hostfs_permission(struct inode *ino, int desired)
{
	char *name;
	int r = 0, w = 0, x = 0, err;

	if (desired & MAY_READ) r = 1;
	if (desired & MAY_WRITE) w = 1;
	if (desired & MAY_EXEC) x = 1;
	name = inode_name(ino, 0);
	if (name == NULL)
		return -ENOMEM;

	if (S_ISCHR(ino->i_mode) || S_ISBLK(ino->i_mode) ||
	    S_ISFIFO(ino->i_mode) || S_ISSOCK(ino->i_mode))
		err = 0;
	else
		err = access_file(name, r, w, x);
	kfree(name);
	if (!err)
		err = generic_permission(ino, desired, NULL);
	return err;
}