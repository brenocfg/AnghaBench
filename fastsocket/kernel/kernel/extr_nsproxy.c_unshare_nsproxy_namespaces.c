#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nsproxy {int dummy; } ;
struct fs_struct {int dummy; } ;
struct TYPE_5__ {struct fs_struct* fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 unsigned long CLONE_NEWIPC ; 
 unsigned long CLONE_NEWNET ; 
 unsigned long CLONE_NEWNS ; 
 unsigned long CLONE_NEWPID ; 
 unsigned long CLONE_NEWUTS ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct nsproxy*) ; 
 int PTR_ERR (struct nsproxy*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct nsproxy* create_new_namespaces (unsigned long,TYPE_1__*,struct fs_struct*) ; 
 TYPE_1__* current ; 
 int ns_cgroup_clone (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_nsproxy (struct nsproxy*) ; 
 int /*<<< orphan*/  task_pid (TYPE_1__*) ; 

int unshare_nsproxy_namespaces(unsigned long unshare_flags,
		struct nsproxy **new_nsp, struct fs_struct *new_fs)
{
	int err = 0;

	if (!(unshare_flags & (CLONE_NEWNS | CLONE_NEWUTS | CLONE_NEWIPC |
			       CLONE_NEWNET | CLONE_NEWPID)))
		return 0;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	*new_nsp = create_new_namespaces(unshare_flags, current,
				new_fs ? new_fs : current->fs);
	if (IS_ERR(*new_nsp)) {
		err = PTR_ERR(*new_nsp);
		goto out;
	}

	err = ns_cgroup_clone(current, task_pid(current));
	if (err)
		put_nsproxy(*new_nsp);

out:
	return err;
}