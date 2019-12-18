#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct mthca_dev {TYPE_1__ cq_table; } ;
struct mthca_cq {int refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_cq_refcount(struct mthca_dev *dev, struct mthca_cq *cq)
{
	int c;

	spin_lock_irq(&dev->cq_table.lock);
	c = cq->refcount;
	spin_unlock_irq(&dev->cq_table.lock);

	return c;
}