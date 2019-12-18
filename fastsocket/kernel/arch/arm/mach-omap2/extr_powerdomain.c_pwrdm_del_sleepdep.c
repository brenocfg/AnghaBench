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
struct powerdomain {int dep_bit; int /*<<< orphan*/  prcm_offs; int /*<<< orphan*/  name; int /*<<< orphan*/  sleepdep_srcs; } ;

/* Variables and functions */
 int EINVAL ; 
 int IS_ERR (struct powerdomain*) ; 
 int /*<<< orphan*/  OMAP3430_CM_SLEEPDEP ; 
 struct powerdomain* _pwrdm_deps_lookup (struct powerdomain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_clear_mod_reg_bits (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_is_omap34xx () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pwrdm_del_sleepdep(struct powerdomain *pwrdm1, struct powerdomain *pwrdm2)
{
	struct powerdomain *p;

	if (!pwrdm1)
		return -EINVAL;

	if (!cpu_is_omap34xx())
		return -EINVAL;

	p = _pwrdm_deps_lookup(pwrdm2, pwrdm1->sleepdep_srcs);
	if (IS_ERR(p)) {
		pr_debug("powerdomain: hardware cannot set/clear sleep "
			 "dependency affecting %s from %s\n", pwrdm1->name,
			 pwrdm2->name);
		return IS_ERR(p);
	}

	pr_debug("powerdomain: will no longer prevent %s from sleeping if "
		 "%s is active\n", pwrdm1->name, pwrdm2->name);

	cm_clear_mod_reg_bits((1 << pwrdm2->dep_bit),
			      pwrdm1->prcm_offs, OMAP3430_CM_SLEEPDEP);

	return 0;
}