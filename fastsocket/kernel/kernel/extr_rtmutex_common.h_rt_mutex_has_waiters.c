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
struct rt_mutex {int /*<<< orphan*/  wait_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  plist_head_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int rt_mutex_has_waiters(struct rt_mutex *lock)
{
	return !plist_head_empty(&lock->wait_list);
}