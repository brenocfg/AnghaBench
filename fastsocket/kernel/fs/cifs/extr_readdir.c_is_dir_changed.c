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
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct cifsInodeInfo {scalar_t__ time; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 

__attribute__((used)) static int is_dir_changed(struct file *file)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	struct cifsInodeInfo *cifsInfo = CIFS_I(inode);

	if (cifsInfo->time == 0)
		return 1; /* directory was changed, perhaps due to unlink */
	else
		return 0;

}