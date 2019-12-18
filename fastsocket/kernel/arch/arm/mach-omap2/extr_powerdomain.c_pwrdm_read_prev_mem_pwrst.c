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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct powerdomain {int banks; int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  OMAP3430_LASTL2FLATMEMSTATEENTERED_MASK ; 
 int /*<<< orphan*/  OMAP3430_LASTMEM1STATEENTERED_MASK ; 
 int /*<<< orphan*/  OMAP3430_LASTMEM2STATEENTERED_MASK ; 
 int /*<<< orphan*/  OMAP3430_LASTSHAREDL2CACHEFLATSTATEENTERED_MASK ; 
 int /*<<< orphan*/  OMAP3430_PM_PREPWSTST ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int prm_read_mod_bits_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pwrdm_read_prev_mem_pwrst(struct powerdomain *pwrdm, u8 bank)
{
	u32 m;

	if (!pwrdm)
		return -EINVAL;

	if (pwrdm->banks < (bank + 1))
		return -EEXIST;

	/*
	 * The register bit names below may not correspond to the
	 * actual names of the bits in each powerdomain's register,
	 * but the type of value returned is the same for each
	 * powerdomain.
	 */
	switch (bank) {
	case 0:
		m = OMAP3430_LASTMEM1STATEENTERED_MASK;
		break;
	case 1:
		m = OMAP3430_LASTMEM2STATEENTERED_MASK;
		break;
	case 2:
		m = OMAP3430_LASTSHAREDL2CACHEFLATSTATEENTERED_MASK;
		break;
	case 3:
		m = OMAP3430_LASTL2FLATMEMSTATEENTERED_MASK;
		break;
	default:
		WARN_ON(1); /* should never happen */
		return -EEXIST;
	}

	return prm_read_mod_bits_shift(pwrdm->prcm_offs,
					OMAP3430_PM_PREPWSTST, m);
}