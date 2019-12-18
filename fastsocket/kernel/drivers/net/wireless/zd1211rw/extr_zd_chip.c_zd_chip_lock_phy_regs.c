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
typedef  int /*<<< orphan*/  u32 ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_REG1 ; 
 int /*<<< orphan*/  UNLOCK_PHY_REGS ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_ioread32_locked (struct zd_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zd_iowrite32_locked (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int zd_chip_lock_phy_regs(struct zd_chip *chip)
{
	int r;
	u32 tmp;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_ioread32_locked(chip, &tmp, CR_REG1);
	if (r) {
		dev_err(zd_chip_dev(chip), "error ioread32(CR_REG1): %d\n", r);
		return r;
	}

	tmp &= ~UNLOCK_PHY_REGS;

	r = zd_iowrite32_locked(chip, tmp, CR_REG1);
	if (r)
		dev_err(zd_chip_dev(chip), "error iowrite32(CR_REG1): %d\n", r);
	return r;
}