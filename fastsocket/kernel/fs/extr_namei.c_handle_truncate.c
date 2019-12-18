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
struct path {TYPE_1__* dentry; } ;
struct inode {int dummy; } ;
struct file {struct path f_path; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ATTR_CTIME ; 
 int ATTR_MTIME ; 
 int ATTR_OPEN ; 
 int do_truncate (TYPE_1__*,int /*<<< orphan*/ ,int,struct file*) ; 
 int get_write_access (struct inode*) ; 
 int locks_verify_locked (struct inode*) ; 
 int /*<<< orphan*/  put_write_access (struct inode*) ; 
 int security_path_truncate (struct path*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int handle_truncate(struct file *filp)
{
	struct path *path = &filp->f_path;
	struct inode *inode = path->dentry->d_inode;
	int error = get_write_access(inode);
	if (error)
		return error;
	/*
	 * Refuse to truncate files with mandatory locks held on them.
	 */
	error = locks_verify_locked(inode);
	if (!error)
		error = security_path_truncate(path, 0,
				       ATTR_MTIME|ATTR_CTIME|ATTR_OPEN);
	if (!error) {
		error = do_truncate(path->dentry, 0,
				    ATTR_MTIME|ATTR_CTIME|ATTR_OPEN,
				    filp);
	}
	put_write_access(inode);
	return error;
}