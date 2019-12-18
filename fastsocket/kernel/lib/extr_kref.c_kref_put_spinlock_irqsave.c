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
struct kref {int /*<<< orphan*/  refcount; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int kref_put_spinlock_irqsave(struct kref *kref,
		void (*release)(struct kref *kref),
		spinlock_t *lock)
{
	unsigned long flags;

	WARN_ON(release == NULL);
	if (atomic_add_unless(&kref->refcount, -1, 1))
		return 0;
	spin_lock_irqsave(lock, flags);
	if (atomic_dec_and_test(&kref->refcount)) {
		release(kref);
		local_irq_restore(flags);
		return 1;
	}
	spin_unlock_irqrestore(lock, flags);
	return 0;
}