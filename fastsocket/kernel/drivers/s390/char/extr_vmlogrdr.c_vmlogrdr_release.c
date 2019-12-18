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
struct vmlogrdr_priv_t {scalar_t__ dev_in_use; int /*<<< orphan*/  autopurge; scalar_t__ autorecording; int /*<<< orphan*/ * path; } ;
struct inode {int dummy; } ;
struct file {struct vmlogrdr_priv_t* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  iucv_path_sever (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int vmlogrdr_recording (struct vmlogrdr_priv_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmlogrdr_release (struct inode *inode, struct file *filp)
{
	int ret;

	struct vmlogrdr_priv_t * logptr = filp->private_data;

	iucv_path_sever(logptr->path, NULL);
	kfree(logptr->path);
	logptr->path = NULL;
	if (logptr->autorecording) {
		ret = vmlogrdr_recording(logptr,0,logptr->autopurge);
		if (ret)
			pr_warning("vmlogrdr: failed to stop "
				   "recording automatically\n");
	}
	logptr->dev_in_use = 0;

	return 0;
}