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
struct zd_rf {int (* switch_radio_off ) (struct zd_rf*) ;} ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int stub1 (struct zd_rf*) ; 
 int zd_chip_lock_phy_regs (struct zd_chip*) ; 
 int zd_chip_unlock_phy_regs (struct zd_chip*) ; 
 struct zd_chip* zd_rf_to_chip (struct zd_rf*) ; 

int zd_switch_radio_off(struct zd_rf *rf)
{
	int r, t;
	struct zd_chip *chip = zd_rf_to_chip(rf);

	/* TODO: move phy regs handling to zd_chip */
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_chip_lock_phy_regs(chip);
	if (r)
		return r;
	t = rf->switch_radio_off(rf);
	r = zd_chip_unlock_phy_regs(chip);
	if (t)
		r = t;
	return r;
}