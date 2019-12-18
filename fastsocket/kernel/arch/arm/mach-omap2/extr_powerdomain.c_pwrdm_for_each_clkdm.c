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
struct powerdomain {struct clockdomain** pwrdm_clkdms; } ;

/* Variables and functions */
 int EINVAL ; 
 int PWRDM_MAX_CLKDMS ; 
 int /*<<< orphan*/  pwrdm_rwlock ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct powerdomain*,struct clockdomain*) ; 

int pwrdm_for_each_clkdm(struct powerdomain *pwrdm,
			 int (*fn)(struct powerdomain *pwrdm,
				   struct clockdomain *clkdm))
{
	unsigned long flags;
	int ret = 0;
	int i;

	if (!fn)
		return -EINVAL;

	read_lock_irqsave(&pwrdm_rwlock, flags);

	for (i = 0; i < PWRDM_MAX_CLKDMS && !ret; i++)
		ret = (*fn)(pwrdm, pwrdm->pwrdm_clkdms[i]);

	read_unlock_irqrestore(&pwrdm_rwlock, flags);

	return ret;
}