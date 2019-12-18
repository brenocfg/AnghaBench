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
struct rt_mutex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_rt_mutex_waiters (struct rt_mutex*) ; 
 int /*<<< orphan*/  rt_mutex_has_waiters (struct rt_mutex*) ; 

__attribute__((used)) static void fixup_rt_mutex_waiters(struct rt_mutex *lock)
{
	if (!rt_mutex_has_waiters(lock))
		clear_rt_mutex_waiters(lock);
}