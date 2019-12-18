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
struct TYPE_2__ {int /*<<< orphan*/  ptr; } ;
struct clockdomain {int /*<<< orphan*/  name; int /*<<< orphan*/  node; TYPE_1__ pwrdm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clkdm_mutex ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_del_clkdm (int /*<<< orphan*/ ,struct clockdomain*) ; 

int clkdm_unregister(struct clockdomain *clkdm)
{
	if (!clkdm)
		return -EINVAL;

	pwrdm_del_clkdm(clkdm->pwrdm.ptr, clkdm);

	mutex_lock(&clkdm_mutex);
	list_del(&clkdm->node);
	mutex_unlock(&clkdm_mutex);

	pr_debug("clockdomain: unregistered %s\n", clkdm->name);

	return 0;
}