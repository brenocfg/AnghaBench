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
struct block_lock {scalar_t__ count; int /*<<< orphan*/  lock; int /*<<< orphan*/  waiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __del_holder (struct block_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wake_many (struct block_lock*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bl_up_read(struct block_lock *lock)
{
	spin_lock(&lock->lock);
	BUG_ON(lock->count <= 0);
	__del_holder(lock, current);
	--lock->count;
	if (!list_empty(&lock->waiters))
		__wake_many(lock);
	spin_unlock(&lock->lock);
}