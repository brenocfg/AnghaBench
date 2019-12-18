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
struct powerdomain {int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OMAP3430_LASTLOGICSTATEENTERED ; 
 int /*<<< orphan*/  OMAP3430_PM_PREPWSTST ; 
 int prm_read_mod_bits_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pwrdm_read_prev_logic_pwrst(struct powerdomain *pwrdm)
{
	if (!pwrdm)
		return -EINVAL;

	/*
	 * The register bit names below may not correspond to the
	 * actual names of the bits in each powerdomain's register,
	 * but the type of value returned is the same for each
	 * powerdomain.
	 */
	return prm_read_mod_bits_shift(pwrdm->prcm_offs, OMAP3430_PM_PREPWSTST,
					OMAP3430_LASTLOGICSTATEENTERED);
}