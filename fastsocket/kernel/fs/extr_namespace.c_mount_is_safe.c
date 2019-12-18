#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_1__* dentry; } ;
struct TYPE_4__ {int i_mode; scalar_t__ i_uid; } ;
struct TYPE_3__ {TYPE_2__* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 scalar_t__ S_ISLNK (int) ; 
 int S_ISVTX ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_uid () ; 
 scalar_t__ inode_permission (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mount_is_safe(struct path *path)
{
	if (capable(CAP_SYS_ADMIN))
		return 0;
	return -EPERM;
#ifdef notyet
	if (S_ISLNK(path->dentry->d_inode->i_mode))
		return -EPERM;
	if (path->dentry->d_inode->i_mode & S_ISVTX) {
		if (current_uid() != path->dentry->d_inode->i_uid)
			return -EPERM;
	}
	if (inode_permission(path->dentry->d_inode, MAY_WRITE))
		return -EPERM;
	return 0;
#endif
}