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
struct waiter {int /*<<< orphan*/  list; scalar_t__ wants_write; int /*<<< orphan*/  task; } ;
struct block_lock {int /*<<< orphan*/  lock; int /*<<< orphan*/  waiters; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __add_holder (struct block_lock*,int /*<<< orphan*/ ) ; 
 scalar_t__ __available_for_read (struct block_lock*) ; 
 int __check_holder (struct block_lock*) ; 
 int /*<<< orphan*/  __wait (struct waiter*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_task_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bl_down_read(struct block_lock *lock)
{
	int r;
	struct waiter w;

	spin_lock(&lock->lock);
	r = __check_holder(lock);
	if (r) {
		spin_unlock(&lock->lock);
		return r;
	}

	if (__available_for_read(lock)) {
		lock->count++;
		__add_holder(lock, current);
		spin_unlock(&lock->lock);
		return 0;
	}

	get_task_struct(current);

	w.task = current;
	w.wants_write = 0;
	list_add_tail(&w.list, &lock->waiters);
	spin_unlock(&lock->lock);

	__wait(&w);
	put_task_struct(current);
	return 0;
}