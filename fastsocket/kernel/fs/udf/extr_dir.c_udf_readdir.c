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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {scalar_t__ f_pos; TYPE_2__ f_path; } ;
typedef  scalar_t__ (* filldir_t ) (void*,char*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int do_udf_readdir (struct inode*,struct file*,scalar_t__ (*) (void*,char*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ),void*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int udf_readdir(struct file *filp, void *dirent, filldir_t filldir)
{
	struct inode *dir = filp->f_path.dentry->d_inode;
	int result;

	lock_kernel();

	if (filp->f_pos == 0) {
		if (filldir(dirent, ".", 1, filp->f_pos, dir->i_ino, DT_DIR) < 0) {
			unlock_kernel();
			return 0;
		}
		filp->f_pos++;
	}

	result = do_udf_readdir(dir, filp, filldir, dirent);
	unlock_kernel();
 	return result;
}