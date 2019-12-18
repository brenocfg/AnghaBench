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
struct clockdomain {int flags; int /*<<< orphan*/  usecount; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CLKDM_CAN_DISABLE_AUTO ; 
 int /*<<< orphan*/  _clkdm_del_autodeps (struct clockdomain*) ; 
 int /*<<< orphan*/  _omap2_clkdm_set_hwsup (struct clockdomain*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

void omap2_clkdm_deny_idle(struct clockdomain *clkdm)
{
	if (!clkdm)
		return;

	if (!(clkdm->flags & CLKDM_CAN_DISABLE_AUTO)) {
		pr_debug("clockdomain: automatic idle transitions cannot be "
			 "disabled on %s\n", clkdm->name);
		return;
	}

	pr_debug("clockdomain: disabling automatic idle transitions for %s\n",
		 clkdm->name);

	_omap2_clkdm_set_hwsup(clkdm, 0);

	if (atomic_read(&clkdm->usecount) > 0)
		_clkdm_del_autodeps(clkdm);
}