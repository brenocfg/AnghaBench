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
struct rt_mutex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rt_mutex_init (struct rt_mutex*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_rt_mutex_proxy_lock (struct rt_mutex*,struct task_struct*) ; 
 int /*<<< orphan*/  rt_mutex_deadlock_account_lock (struct rt_mutex*,struct task_struct*) ; 
 int /*<<< orphan*/  rt_mutex_set_owner (struct rt_mutex*,struct task_struct*,int /*<<< orphan*/ ) ; 

void rt_mutex_init_proxy_locked(struct rt_mutex *lock,
				struct task_struct *proxy_owner)
{
	__rt_mutex_init(lock, NULL);
	debug_rt_mutex_proxy_lock(lock, proxy_owner);
	rt_mutex_set_owner(lock, proxy_owner, 0);
	rt_mutex_deadlock_account_lock(lock, proxy_owner);
}