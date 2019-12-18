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
struct powerdomain {int dummy; } ;
struct TYPE_2__ {struct powerdomain* ptr; int /*<<< orphan*/  name; } ;
struct clockdomain {int /*<<< orphan*/  name; int /*<<< orphan*/  node; TYPE_1__ pwrdm; int /*<<< orphan*/  omap_chip; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ _clkdm_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdm_list ; 
 int /*<<< orphan*/  clkdm_mutex ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_chip_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_add_clkdm (struct powerdomain*,struct clockdomain*) ; 
 struct powerdomain* pwrdm_lookup (int /*<<< orphan*/ ) ; 

int clkdm_register(struct clockdomain *clkdm)
{
	int ret = -EINVAL;
	struct powerdomain *pwrdm;

	if (!clkdm || !clkdm->name)
		return -EINVAL;

	if (!omap_chip_is(clkdm->omap_chip))
		return -EINVAL;

	pwrdm = pwrdm_lookup(clkdm->pwrdm.name);
	if (!pwrdm) {
		pr_err("clockdomain: %s: powerdomain %s does not exist\n",
			clkdm->name, clkdm->pwrdm.name);
		return -EINVAL;
	}
	clkdm->pwrdm.ptr = pwrdm;

	mutex_lock(&clkdm_mutex);
	/* Verify that the clockdomain is not already registered */
	if (_clkdm_lookup(clkdm->name)) {
		ret = -EEXIST;
		goto cr_unlock;
	}

	list_add(&clkdm->node, &clkdm_list);

	pwrdm_add_clkdm(pwrdm, clkdm);

	pr_debug("clockdomain: registered %s\n", clkdm->name);
	ret = 0;

cr_unlock:
	mutex_unlock(&clkdm_mutex);

	return ret;
}