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
struct task_struct {int dummy; } ;
struct rt_mutex {int dummy; } ;
struct TYPE_2__ {struct task_struct* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt_mutex_has_waiters (struct rt_mutex*) ; 
 TYPE_1__* rt_mutex_top_waiter (struct rt_mutex*) ; 

struct task_struct *rt_mutex_next_owner(struct rt_mutex *lock)
{
	if (!rt_mutex_has_waiters(lock))
		return NULL;

	return rt_mutex_top_waiter(lock)->task;
}