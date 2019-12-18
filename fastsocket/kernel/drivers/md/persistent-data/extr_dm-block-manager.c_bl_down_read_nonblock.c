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
struct block_lock {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  __add_holder (struct block_lock*,int /*<<< orphan*/ ) ; 
 scalar_t__ __available_for_read (struct block_lock*) ; 
 int __check_holder (struct block_lock*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bl_down_read_nonblock(struct block_lock *lock)
{
	int r;

	spin_lock(&lock->lock);
	r = __check_holder(lock);
	if (r)
		goto out;

	if (__available_for_read(lock)) {
		lock->count++;
		__add_holder(lock, current);
		r = 0;
	} else
		r = -EWOULDBLOCK;

out:
	spin_unlock(&lock->lock);
	return r;
}