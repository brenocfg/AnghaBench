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

/* Variables and functions */
 int pwrdm_for_each_nolock (int (*) (struct powerdomain*,void*),void*) ; 
 int /*<<< orphan*/  pwrdm_rwlock ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pwrdm_for_each(int (*fn)(struct powerdomain *pwrdm, void *user),
			void *user)
{
	unsigned long flags;
	int ret;

	read_lock_irqsave(&pwrdm_rwlock, flags);
	ret = pwrdm_for_each_nolock(fn, user);
	read_unlock_irqrestore(&pwrdm_rwlock, flags);

	return ret;
}