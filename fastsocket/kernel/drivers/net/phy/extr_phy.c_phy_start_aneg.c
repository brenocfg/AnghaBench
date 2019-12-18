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
struct phy_device {scalar_t__ autoneg; scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  link_timeout; TYPE_1__* drv; } ;
struct TYPE_2__ {int (* config_aneg ) (struct phy_device*) ;} ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ PHY_AN ; 
 int /*<<< orphan*/  PHY_AN_TIMEOUT ; 
 int /*<<< orphan*/  PHY_FORCE_TIMEOUT ; 
 scalar_t__ PHY_FORCING ; 
 scalar_t__ PHY_HALTED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_sanitize_settings (struct phy_device*) ; 
 int stub1 (struct phy_device*) ; 

int phy_start_aneg(struct phy_device *phydev)
{
	int err;

	mutex_lock(&phydev->lock);

	if (AUTONEG_DISABLE == phydev->autoneg)
		phy_sanitize_settings(phydev);

	err = phydev->drv->config_aneg(phydev);

	if (err < 0)
		goto out_unlock;

	if (phydev->state != PHY_HALTED) {
		if (AUTONEG_ENABLE == phydev->autoneg) {
			phydev->state = PHY_AN;
			phydev->link_timeout = PHY_AN_TIMEOUT;
		} else {
			phydev->state = PHY_FORCING;
			phydev->link_timeout = PHY_FORCE_TIMEOUT;
		}
	}

out_unlock:
	mutex_unlock(&phydev->lock);
	return err;
}