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
struct TYPE_2__ {scalar_t__ mode; } ;
struct ldc_channel {int flags; scalar_t__ hs_state; int /*<<< orphan*/  lock; TYPE_1__ cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 int LDC_FLAG_ALLOCED_QUEUES ; 
 int LDC_FLAG_REGISTERED_QUEUES ; 
 scalar_t__ LDC_HS_OPEN ; 
 scalar_t__ LDC_MODE_RAW ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int start_handshake (struct ldc_channel*) ; 

int ldc_connect(struct ldc_channel *lp)
{
	unsigned long flags;
	int err;

	if (lp->cfg.mode == LDC_MODE_RAW)
		return -EINVAL;

	spin_lock_irqsave(&lp->lock, flags);

	if (!(lp->flags & LDC_FLAG_ALLOCED_QUEUES) ||
	    !(lp->flags & LDC_FLAG_REGISTERED_QUEUES) ||
	    lp->hs_state != LDC_HS_OPEN)
		err = -EINVAL;
	else
		err = start_handshake(lp);

	spin_unlock_irqrestore(&lp->lock, flags);

	return err;
}