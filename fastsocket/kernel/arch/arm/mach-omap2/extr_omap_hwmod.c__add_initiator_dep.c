#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omap_hwmod {TYPE_3__* _clk; } ;
struct TYPE_6__ {TYPE_2__* clkdm; } ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_5__ {TYPE_1__ pwrdm; } ;

/* Variables and functions */
 int EINVAL ; 
 int pwrdm_add_sleepdep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _add_initiator_dep(struct omap_hwmod *oh, struct omap_hwmod *init_oh)
{
	if (!oh->_clk)
		return -EINVAL;

	return pwrdm_add_sleepdep(oh->_clk->clkdm->pwrdm.ptr,
				  init_oh->_clk->clkdm->pwrdm.ptr);
}