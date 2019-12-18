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
struct block_lock {scalar_t__ count; int /*<<< orphan*/  waiters; } ;

/* Variables and functions */
 scalar_t__ MAX_HOLDERS ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __available_for_read(struct block_lock *lock)
{
	return lock->count >= 0 &&
		lock->count < MAX_HOLDERS &&
		list_empty(&lock->waiters);
}