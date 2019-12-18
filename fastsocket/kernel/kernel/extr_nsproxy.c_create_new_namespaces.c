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
struct task_struct {TYPE_1__* nsproxy; } ;
struct nsproxy {scalar_t__ mnt_ns; scalar_t__ uts_ns; scalar_t__ ipc_ns; scalar_t__ pid_ns; scalar_t__ net_ns; } ;
struct fs_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  net_ns; int /*<<< orphan*/  pid_ns; int /*<<< orphan*/  ipc_ns; int /*<<< orphan*/  uts_ns; int /*<<< orphan*/  mnt_ns; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct nsproxy* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ copy_ipcs (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_mnt_ns (unsigned long,int /*<<< orphan*/ ,struct fs_struct*) ; 
 scalar_t__ copy_net_ns (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_pid_ns (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_utsname (unsigned long,int /*<<< orphan*/ ) ; 
 struct nsproxy* create_nsproxy () ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nsproxy*) ; 
 int /*<<< orphan*/  nsproxy_cachep ; 
 int /*<<< orphan*/  put_ipc_ns (scalar_t__) ; 
 int /*<<< orphan*/  put_mnt_ns (scalar_t__) ; 
 int /*<<< orphan*/  put_pid_ns (scalar_t__) ; 
 int /*<<< orphan*/  put_uts_ns (scalar_t__) ; 

__attribute__((used)) static struct nsproxy *create_new_namespaces(unsigned long flags,
			struct task_struct *tsk, struct fs_struct *new_fs)
{
	struct nsproxy *new_nsp;
	int err;

	new_nsp = create_nsproxy();
	if (!new_nsp)
		return ERR_PTR(-ENOMEM);

	new_nsp->mnt_ns = copy_mnt_ns(flags, tsk->nsproxy->mnt_ns, new_fs);
	if (IS_ERR(new_nsp->mnt_ns)) {
		err = PTR_ERR(new_nsp->mnt_ns);
		goto out_ns;
	}

	new_nsp->uts_ns = copy_utsname(flags, tsk->nsproxy->uts_ns);
	if (IS_ERR(new_nsp->uts_ns)) {
		err = PTR_ERR(new_nsp->uts_ns);
		goto out_uts;
	}

	new_nsp->ipc_ns = copy_ipcs(flags, tsk->nsproxy->ipc_ns);
	if (IS_ERR(new_nsp->ipc_ns)) {
		err = PTR_ERR(new_nsp->ipc_ns);
		goto out_ipc;
	}

	new_nsp->pid_ns = copy_pid_ns(flags, tsk->nsproxy->pid_ns);
	if (IS_ERR(new_nsp->pid_ns)) {
		err = PTR_ERR(new_nsp->pid_ns);
		goto out_pid;
	}

	new_nsp->net_ns = copy_net_ns(flags, tsk->nsproxy->net_ns);
	if (IS_ERR(new_nsp->net_ns)) {
		err = PTR_ERR(new_nsp->net_ns);
		goto out_net;
	}

	return new_nsp;

out_net:
	if (new_nsp->pid_ns)
		put_pid_ns(new_nsp->pid_ns);
out_pid:
	if (new_nsp->ipc_ns)
		put_ipc_ns(new_nsp->ipc_ns);
out_ipc:
	if (new_nsp->uts_ns)
		put_uts_ns(new_nsp->uts_ns);
out_uts:
	if (new_nsp->mnt_ns)
		put_mnt_ns(new_nsp->mnt_ns);
out_ns:
	kmem_cache_free(nsproxy_cachep, new_nsp);
	return ERR_PTR(err);
}