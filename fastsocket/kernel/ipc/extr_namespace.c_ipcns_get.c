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
struct task_struct {int dummy; } ;
struct nsproxy {int /*<<< orphan*/  ipc_ns; } ;
typedef  void ipc_namespace ;

/* Variables and functions */
 void* get_ipc_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct nsproxy* task_nsproxy (struct task_struct*) ; 

__attribute__((used)) static void *ipcns_get(struct task_struct *task)
{
	struct ipc_namespace *ns = NULL;
	struct nsproxy *nsproxy;

	rcu_read_lock();
	nsproxy = task_nsproxy(task);
	if (nsproxy)
		ns = get_ipc_ns(nsproxy->ipc_ns);
	rcu_read_unlock();

	return ns;
}