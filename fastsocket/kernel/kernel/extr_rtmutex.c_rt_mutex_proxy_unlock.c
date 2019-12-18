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
 int /*<<< orphan*/  debug_rt_mutex_proxy_unlock (struct rt_mutex*) ; 
 int /*<<< orphan*/  rt_mutex_deadlock_account_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  rt_mutex_set_owner (struct rt_mutex*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rt_mutex_proxy_unlock(struct rt_mutex *lock,
			   struct task_struct *proxy_owner)
{
	debug_rt_mutex_proxy_unlock(lock);
	rt_mutex_set_owner(lock, NULL, 0);
	rt_mutex_deadlock_account_unlock(proxy_owner);
}