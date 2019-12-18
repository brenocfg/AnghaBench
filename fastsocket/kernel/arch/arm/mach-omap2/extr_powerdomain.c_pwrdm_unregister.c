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
struct powerdomain {int /*<<< orphan*/  name; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_rwlock ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pwrdm_unregister(struct powerdomain *pwrdm)
{
	unsigned long flags;

	if (!pwrdm)
		return -EINVAL;

	write_lock_irqsave(&pwrdm_rwlock, flags);
	list_del(&pwrdm->node);
	write_unlock_irqrestore(&pwrdm_rwlock, flags);

	pr_debug("powerdomain: unregistered %s\n", pwrdm->name);

	return 0;
}