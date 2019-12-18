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
struct powerdomain {int dep_bit; int /*<<< orphan*/  prcm_offs; int /*<<< orphan*/  name; int /*<<< orphan*/  wkdep_srcs; } ;

/* Variables and functions */
 int EINVAL ; 
 int IS_ERR (struct powerdomain*) ; 
 int /*<<< orphan*/  PM_WKDEP ; 
 struct powerdomain* _pwrdm_deps_lookup (struct powerdomain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prm_set_mod_reg_bits (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pwrdm_add_wkdep(struct powerdomain *pwrdm1, struct powerdomain *pwrdm2)
{
	struct powerdomain *p;

	if (!pwrdm1)
		return -EINVAL;

	p = _pwrdm_deps_lookup(pwrdm2, pwrdm1->wkdep_srcs);
	if (IS_ERR(p)) {
		pr_debug("powerdomain: hardware cannot set/clear wake up of "
			 "%s when %s wakes up\n", pwrdm1->name, pwrdm2->name);
		return IS_ERR(p);
	}

	pr_debug("powerdomain: hardware will wake up %s when %s wakes up\n",
		 pwrdm1->name, pwrdm2->name);

	prm_set_mod_reg_bits((1 << pwrdm2->dep_bit),
			     pwrdm1->prcm_offs, PM_WKDEP);

	return 0;
}