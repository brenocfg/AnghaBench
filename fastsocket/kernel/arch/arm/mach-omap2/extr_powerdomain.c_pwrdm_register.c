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
struct powerdomain {int /*<<< orphan*/  name; int /*<<< orphan*/  node; int /*<<< orphan*/  omap_chip; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ _pwrdm_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_chip_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_list ; 
 int /*<<< orphan*/  pwrdm_rwlock ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pwrdm_register(struct powerdomain *pwrdm)
{
	unsigned long flags;
	int ret = -EINVAL;

	if (!pwrdm)
		return -EINVAL;

	if (!omap_chip_is(pwrdm->omap_chip))
		return -EINVAL;

	write_lock_irqsave(&pwrdm_rwlock, flags);
	if (_pwrdm_lookup(pwrdm->name)) {
		ret = -EEXIST;
		goto pr_unlock;
	}

	list_add(&pwrdm->node, &pwrdm_list);

	pr_debug("powerdomain: registered %s\n", pwrdm->name);
	ret = 0;

pr_unlock:
	write_unlock_irqrestore(&pwrdm_rwlock, flags);

	return ret;
}