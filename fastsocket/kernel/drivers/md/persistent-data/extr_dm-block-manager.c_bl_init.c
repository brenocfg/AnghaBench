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
struct block_lock {int /*<<< orphan*/ ** holders; int /*<<< orphan*/  waiters; scalar_t__ count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_HOLDERS ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bl_init(struct block_lock *lock)
{
	int i;

	spin_lock_init(&lock->lock);
	lock->count = 0;
	INIT_LIST_HEAD(&lock->waiters);
	for (i = 0; i < MAX_HOLDERS; i++)
		lock->holders[i] = NULL;
}