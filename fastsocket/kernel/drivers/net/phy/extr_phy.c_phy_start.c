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
struct phy_device {int state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  PHY_HALTED 130 
 int PHY_PENDING ; 
#define  PHY_READY 129 
 int PHY_RESUMING ; 
#define  PHY_STARTING 128 
 int PHY_UP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void phy_start(struct phy_device *phydev)
{
	mutex_lock(&phydev->lock);

	switch (phydev->state) {
		case PHY_STARTING:
			phydev->state = PHY_PENDING;
			break;
		case PHY_READY:
			phydev->state = PHY_UP;
			break;
		case PHY_HALTED:
			phydev->state = PHY_RESUMING;
		default:
			break;
	}
	mutex_unlock(&phydev->lock);
}