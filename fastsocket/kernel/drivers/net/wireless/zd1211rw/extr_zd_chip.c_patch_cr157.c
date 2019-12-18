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
typedef  int u16 ;
struct zd_chip {int /*<<< orphan*/  patch_cr157; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_PHY_REG ; 
 int /*<<< orphan*/  ZD_CR157 ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_ioread16_locked (struct zd_chip*,int*,int /*<<< orphan*/ ) ; 
 int zd_iowrite32_locked (struct zd_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_cr157(struct zd_chip *chip)
{
	int r;
	u16 value;

	if (!chip->patch_cr157)
		return 0;

	r = zd_ioread16_locked(chip, &value, E2P_PHY_REG);
	if (r)
		return r;

	dev_dbg_f(zd_chip_dev(chip), "patching value %x\n", value >> 8);
	return zd_iowrite32_locked(chip, value >> 8, ZD_CR157);
}