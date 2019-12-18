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
struct rt_mutex {int /*<<< orphan*/  wait_lock; int /*<<< orphan*/  wait_list; int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_rt_mutex_init (struct rt_mutex*,char const*) ; 
 int /*<<< orphan*/  plist_head_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void __rt_mutex_init(struct rt_mutex *lock, const char *name)
{
	lock->owner = NULL;
	spin_lock_init(&lock->wait_lock);
	plist_head_init(&lock->wait_list, &lock->wait_lock);

	debug_rt_mutex_init(lock, name);
}