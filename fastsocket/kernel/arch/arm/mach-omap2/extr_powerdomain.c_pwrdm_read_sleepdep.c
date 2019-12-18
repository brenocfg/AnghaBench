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
 int /*<<< orphan*/  cpu_is_omap34xx () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int prm_read_mod_bits_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int pwrdm_read_sleepdep(struct powerdomain *pwrdm1, struct powerdomain *pwrdm2)
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

	return prm_read_mod_bits_shift(pwrdm1->prcm_offs, OMAP3430_CM_SLEEPDEP,
					(1 << pwrdm2->dep_bit));
}