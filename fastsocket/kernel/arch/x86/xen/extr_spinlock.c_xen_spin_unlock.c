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
struct xen_spinlock {int /*<<< orphan*/  spinners; scalar_t__ lock; } ;
struct raw_spinlock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STATS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  released ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_spin_unlock_slow (struct xen_spinlock*) ; 

__attribute__((used)) static void xen_spin_unlock(struct raw_spinlock *lock)
{
	struct xen_spinlock *xl = (struct xen_spinlock *)lock;

	ADD_STATS(released, 1);

	smp_wmb();		/* make sure no writes get moved after unlock */
	xl->lock = 0;		/* release lock */

	/*
	 * Make sure unlock happens before checking for waiting
	 * spinners.  We need a strong barrier to enforce the
	 * write-read ordering to different memory locations, as the
	 * CPU makes no implied guarantees about their ordering.
	 */
	mb();

	if (unlikely(xl->spinners))
		xen_spin_unlock_slow(xl);
}