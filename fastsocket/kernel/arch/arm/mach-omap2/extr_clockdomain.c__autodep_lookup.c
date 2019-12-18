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
struct clkdm_pwrdm_autodep {TYPE_1__ pwrdm; int /*<<< orphan*/  omap_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct powerdomain* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_chip_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 struct powerdomain* pwrdm_lookup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _autodep_lookup(struct clkdm_pwrdm_autodep *autodep)
{
	struct powerdomain *pwrdm;

	if (!autodep)
		return;

	if (!omap_chip_is(autodep->omap_chip))
		return;

	pwrdm = pwrdm_lookup(autodep->pwrdm.name);
	if (!pwrdm) {
		pr_err("clockdomain: autodeps: powerdomain %s does not exist\n",
			 autodep->pwrdm.name);
		pwrdm = ERR_PTR(-ENOENT);
	}
	autodep->pwrdm.ptr = pwrdm;
}