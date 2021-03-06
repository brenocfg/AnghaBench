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
struct mutex {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread_info () ; 

__attribute__((used)) static inline void mutex_set_owner(struct mutex *lock)
{
	lock->owner = current_thread_info();
}