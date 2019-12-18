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
struct clockdomain {int dummy; } ;
struct TYPE_2__ {scalar_t__ ptr; } ;
struct clkdm_pwrdm_autodep {TYPE_1__ pwrdm; } ;

/* Variables and functions */
 int /*<<< orphan*/  _autodep_lookup (struct clkdm_pwrdm_autodep*) ; 
 struct clkdm_pwrdm_autodep* autodeps ; 
 int /*<<< orphan*/  clkdm_register (struct clockdomain*) ; 

void clkdm_init(struct clockdomain **clkdms,
		struct clkdm_pwrdm_autodep *init_autodeps)
{
	struct clockdomain **c = NULL;
	struct clkdm_pwrdm_autodep *autodep = NULL;

	if (clkdms)
		for (c = clkdms; *c; c++)
			clkdm_register(*c);

	autodeps = init_autodeps;
	if (autodeps)
		for (autodep = autodeps; autodep->pwrdm.ptr; autodep++)
			_autodep_lookup(autodep);
}