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
struct c2_dev {int /*<<< orphan*/  lock; struct c2_cq** qptr_array; } ;
struct c2_cq {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct c2_cq *c2_cq_get(struct c2_dev *c2dev, int cqn)
{
	struct c2_cq *cq;
	unsigned long flags;

	spin_lock_irqsave(&c2dev->lock, flags);
	cq = c2dev->qptr_array[cqn];
	if (!cq) {
		spin_unlock_irqrestore(&c2dev->lock, flags);
		return NULL;
	}
	atomic_inc(&cq->refcount);
	spin_unlock_irqrestore(&c2dev->lock, flags);
	return cq;
}