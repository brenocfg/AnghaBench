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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {int f_mode; TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  cFYI (int,char*,struct inode*,struct file*,int) ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 

int cifs_flush(struct file *file, fl_owner_t id)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	int rc = 0;

	if (file->f_mode & FMODE_WRITE)
		rc = filemap_write_and_wait(inode->i_mapping);

	cFYI(1, "Flush inode %p file %p rc %d", inode, file, rc);

	return rc;
}