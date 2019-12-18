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
struct nsproxy {int /*<<< orphan*/  net_ns; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct net* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESRCH ; 
 struct task_struct* find_task_by_vpid (int /*<<< orphan*/ ) ; 
 struct net* get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct nsproxy* task_nsproxy (struct task_struct*) ; 

struct net *get_net_ns_by_pid(pid_t pid)
{
	struct task_struct *tsk;
	struct net *net;

	/* Lookup the network namespace */
	net = ERR_PTR(-ESRCH);
	rcu_read_lock();
	tsk = find_task_by_vpid(pid);
	if (tsk) {
		struct nsproxy *nsproxy;
		nsproxy = task_nsproxy(tsk);
		if (nsproxy)
			net = get_net(nsproxy->net_ns);
	}
	rcu_read_unlock();
	return net;
}