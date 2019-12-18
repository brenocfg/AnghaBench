#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* ptr; } ;
struct clockdomain {TYPE_1__ pwrdm; } ;
struct TYPE_9__ {TYPE_4__* ptr; } ;
struct clkdm_pwrdm_autodep {TYPE_2__ pwrdm; int /*<<< orphan*/  omap_chip; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_4__*) ; 
 struct clkdm_pwrdm_autodep* autodeps ; 
 int /*<<< orphan*/  omap_chip_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_add_sleepdep (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  pwrdm_add_wkdep (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static void _clkdm_add_autodeps(struct clockdomain *clkdm)
{
	struct clkdm_pwrdm_autodep *autodep;

	for (autodep = autodeps; autodep->pwrdm.ptr; autodep++) {
		if (IS_ERR(autodep->pwrdm.ptr))
			continue;

		if (!omap_chip_is(autodep->omap_chip))
			continue;

		pr_debug("clockdomain: adding %s sleepdep/wkdep for "
			 "pwrdm %s\n", autodep->pwrdm.ptr->name,
			 clkdm->pwrdm.ptr->name);

		pwrdm_add_sleepdep(clkdm->pwrdm.ptr, autodep->pwrdm.ptr);
		pwrdm_add_wkdep(clkdm->pwrdm.ptr, autodep->pwrdm.ptr);
	}
}