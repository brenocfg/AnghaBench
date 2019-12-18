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
struct inode {int dummy; } ;
struct TYPE_3__ {struct dentry* dentry; } ;
struct file {int f_mode; TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  openers; } ;

/* Variables and functions */
 int O_ACCMODE ; 
 TYPE_2__* SMB_I (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int smb_open (struct dentry*,int) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
smb_file_open(struct inode *inode, struct file * file)
{
	int result;
	struct dentry *dentry = file->f_path.dentry;
	int smb_mode = (file->f_mode & O_ACCMODE) - 1;

	lock_kernel();
	result = smb_open(dentry, smb_mode);
	if (result)
		goto out;
	SMB_I(inode)->openers++;
out:
	unlock_kernel();
	return result;
}