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
struct ttm_lock {scalar_t__ rw; scalar_t__ flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  signal; int /*<<< orphan*/  kill_takers; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __ttm_read_trylock(struct ttm_lock *lock, bool *locked)
{
	bool block = true;

	*locked = false;

	spin_lock(&lock->lock);
	if (unlikely(lock->kill_takers)) {
		send_sig(lock->signal, current, 0);
		spin_unlock(&lock->lock);
		return false;
	}
	if (lock->rw >= 0 && lock->flags == 0) {
		++lock->rw;
		block = false;
		*locked = true;
	} else if (lock->flags == 0) {
		block = false;
	}
	spin_unlock(&lock->lock);

	return !block;
}