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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  mnt; } ;
struct file {int f_mode; TYPE_2__ f_path; TYPE_1__* f_dentry; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int __mnt_want_write (int /*<<< orphan*/ ) ; 
 int mnt_clone_write (int /*<<< orphan*/ ) ; 
 scalar_t__ special_file (int /*<<< orphan*/ ) ; 

int __mnt_want_write_file(struct file *file)
{
	struct inode *inode = file->f_dentry->d_inode;
	if (!(file->f_mode & FMODE_WRITE) || special_file(inode->i_mode))
		return __mnt_want_write(file->f_path.mnt);
	else
		return mnt_clone_write(file->f_path.mnt);
}