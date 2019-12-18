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
struct ldc_channel {scalar_t__ hs_state; int /*<<< orphan*/  lock; TYPE_1__* mops; } ;
struct TYPE_2__ {int (* write ) (struct ldc_channel*,void const*,unsigned int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 scalar_t__ LDC_HS_COMPLETE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct ldc_channel*,void const*,unsigned int) ; 

int ldc_write(struct ldc_channel *lp, const void *buf, unsigned int size)
{
	unsigned long flags;
	int err;

	if (!buf)
		return -EINVAL;

	if (!size)
		return 0;

	spin_lock_irqsave(&lp->lock, flags);

	if (lp->hs_state != LDC_HS_COMPLETE)
		err = -ENOTCONN;
	else
		err = lp->mops->write(lp, buf, size);

	spin_unlock_irqrestore(&lp->lock, flags);

	return err;
}