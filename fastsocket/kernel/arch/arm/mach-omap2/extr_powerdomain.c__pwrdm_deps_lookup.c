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
struct pwrdm_dep {struct powerdomain* pwrdm; scalar_t__ pwrdm_name; int /*<<< orphan*/  omap_chip; } ;
struct powerdomain {int /*<<< orphan*/  omap_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct powerdomain* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_chip_is (int /*<<< orphan*/ ) ; 
 struct powerdomain* pwrdm_lookup (scalar_t__) ; 

__attribute__((used)) static struct powerdomain *_pwrdm_deps_lookup(struct powerdomain *pwrdm,
					      struct pwrdm_dep *deps)
{
	struct pwrdm_dep *pd;

	if (!pwrdm || !deps || !omap_chip_is(pwrdm->omap_chip))
		return ERR_PTR(-EINVAL);

	for (pd = deps; pd->pwrdm_name; pd++) {

		if (!omap_chip_is(pd->omap_chip))
			continue;

		if (!pd->pwrdm && pd->pwrdm_name)
			pd->pwrdm = pwrdm_lookup(pd->pwrdm_name);

		if (pd->pwrdm == pwrdm)
			break;

	}

	if (!pd->pwrdm_name)
		return ERR_PTR(-ENOENT);

	return pd->pwrdm;
}