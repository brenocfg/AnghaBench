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
struct iso_directory_record {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  filldir_t ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int do_isofs_readdir (struct inode*,struct file*,void*,int /*<<< orphan*/ ,char*,struct iso_directory_record*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int isofs_readdir(struct file *filp,
		void *dirent, filldir_t filldir)
{
	int result;
	char *tmpname;
	struct iso_directory_record *tmpde;
	struct inode *inode = filp->f_path.dentry->d_inode;

	tmpname = (char *)__get_free_page(GFP_KERNEL);
	if (tmpname == NULL)
		return -ENOMEM;

	lock_kernel();
	tmpde = (struct iso_directory_record *) (tmpname+1024);

	result = do_isofs_readdir(inode, filp, dirent, filldir, tmpname, tmpde);

	free_page((unsigned long) tmpname);
	unlock_kernel();
	return result;
}