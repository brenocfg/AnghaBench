#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int extpagain; } ;
struct TYPE_5__ {int extpagain; } ;
struct TYPE_4__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int ipa2g_on; int ipa5g_on; TYPE_3__ srom_fem5g; TYPE_2__ srom_fem2g; TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 

void wlc_phy_txpower_ipa_upd(struct brcms_phy *pi)
{

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		pi->ipa2g_on = (pi->srom_fem2g.extpagain == 2);
		pi->ipa5g_on = (pi->srom_fem5g.extpagain == 2);
	} else {
		pi->ipa2g_on = false;
		pi->ipa5g_on = false;
	}
}