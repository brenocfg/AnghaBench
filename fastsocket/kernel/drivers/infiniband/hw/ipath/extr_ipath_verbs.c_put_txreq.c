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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct ipath_verbs_txreq {TYPE_1__ txreq; } ;
struct ipath_ibdev {int /*<<< orphan*/  pending_lock; int /*<<< orphan*/  txreq_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void put_txreq(struct ipath_ibdev *dev,
			     struct ipath_verbs_txreq *tx)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->pending_lock, flags);
	list_add(&tx->txreq.list, &dev->txreq_free);
	spin_unlock_irqrestore(&dev->pending_lock, flags);
}