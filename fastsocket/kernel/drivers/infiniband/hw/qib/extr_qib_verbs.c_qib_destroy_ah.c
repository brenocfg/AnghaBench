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
struct qib_ibdev {int /*<<< orphan*/  n_ahs_lock; int /*<<< orphan*/  n_ahs_allocated; } ;
struct qib_ah {int /*<<< orphan*/  refcount; } ;
struct ib_ah {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qib_ah*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct qib_ah* to_iah (struct ib_ah*) ; 
 struct qib_ibdev* to_idev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_destroy_ah(struct ib_ah *ibah)
{
	struct qib_ibdev *dev = to_idev(ibah->device);
	struct qib_ah *ah = to_iah(ibah);
	unsigned long flags;

	if (atomic_read(&ah->refcount) != 0)
		return -EBUSY;

	spin_lock_irqsave(&dev->n_ahs_lock, flags);
	dev->n_ahs_allocated--;
	spin_unlock_irqrestore(&dev->n_ahs_lock, flags);

	kfree(ah);

	return 0;
}