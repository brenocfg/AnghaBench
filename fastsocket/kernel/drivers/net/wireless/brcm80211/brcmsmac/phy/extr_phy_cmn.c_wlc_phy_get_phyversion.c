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
typedef  scalar_t__ u16 ;
struct brcms_phy_pub {int dummy; } ;
struct TYPE_2__ {scalar_t__ radiorev; scalar_t__ radioid; scalar_t__ phy_rev; scalar_t__ phy_type; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */

bool
wlc_phy_get_phyversion(struct brcms_phy_pub *pih, u16 *phytype, u16 *phyrev,
		       u16 *radioid, u16 *radiover)
{
	struct brcms_phy *pi = (struct brcms_phy *) pih;
	*phytype = (u16) pi->pubpi.phy_type;
	*phyrev = (u16) pi->pubpi.phy_rev;
	*radioid = pi->pubpi.radioid;
	*radiover = pi->pubpi.radiorev;

	return true;
}