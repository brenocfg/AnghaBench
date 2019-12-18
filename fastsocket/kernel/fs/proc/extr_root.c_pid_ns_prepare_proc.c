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
struct vfsmount {int dummy; } ;
struct pid_namespace {struct vfsmount* proc_mnt; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int PTR_ERR (struct vfsmount*) ; 
 struct vfsmount* kern_mount_data (int /*<<< orphan*/ *,struct pid_namespace*) ; 
 int /*<<< orphan*/  proc_fs_type ; 

int pid_ns_prepare_proc(struct pid_namespace *ns)
{
	struct vfsmount *mnt;

	mnt = kern_mount_data(&proc_fs_type, ns);
	if (IS_ERR(mnt))
		return PTR_ERR(mnt);

	ns->proc_mnt = mnt;
	return 0;
}