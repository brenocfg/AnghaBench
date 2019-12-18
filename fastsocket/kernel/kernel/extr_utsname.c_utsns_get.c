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
typedef  void uts_namespace ;
struct task_struct {int dummy; } ;
struct nsproxy {void* uts_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_uts_ns (void*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct nsproxy* task_nsproxy (struct task_struct*) ; 

__attribute__((used)) static void *utsns_get(struct task_struct *task)
{
	struct uts_namespace *ns = NULL;
	struct nsproxy *nsproxy;

	rcu_read_lock();
	nsproxy = task_nsproxy(task);
	if (nsproxy) {
		ns = nsproxy->uts_ns;
		get_uts_ns(ns);
	}
	rcu_read_unlock();

	return ns;
}