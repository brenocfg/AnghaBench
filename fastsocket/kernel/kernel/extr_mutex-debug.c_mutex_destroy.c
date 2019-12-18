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
struct mutex {int /*<<< orphan*/ * magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOCKS_WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (struct mutex*) ; 

void mutex_destroy(struct mutex *lock)
{
	DEBUG_LOCKS_WARN_ON(mutex_is_locked(lock));
	lock->magic = NULL;
}