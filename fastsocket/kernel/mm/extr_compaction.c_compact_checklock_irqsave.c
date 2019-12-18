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
struct compact_control {int contended; int /*<<< orphan*/  sync; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ need_resched () ; 
 scalar_t__ spin_is_contended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool compact_checklock_irqsave(spinlock_t *lock, unsigned long *flags,
				      bool locked, struct compact_control *cc)
{
	if (need_resched() || spin_is_contended(lock)) {
		if (locked) {
			spin_unlock_irqrestore(lock, *flags);
			locked = false;
		}

		/* async aborts if taking too long or contended */
		if (!cc->sync) {
			cc->contended = true;
			return false;
		}

		cond_resched();
		if (fatal_signal_pending(current))
			return false;
	}

	if (!locked)
		spin_lock_irqsave(lock, *flags);
	return true;
}