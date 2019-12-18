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
struct brcms_phy {scalar_t__ nphy_deaf_count; TYPE_1__* sh; } ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_stay_in_carriersearch_nphy (struct brcms_phy*,int) ; 

void wlc_nphy_deaf_mode(struct brcms_phy *pi, bool mode)
{
	wlapi_suspend_mac_and_wait(pi->sh->physhim);

	if (mode) {
		if (pi->nphy_deaf_count == 0)
			wlc_phy_stay_in_carriersearch_nphy(pi, true);
	} else if (pi->nphy_deaf_count > 0) {
		wlc_phy_stay_in_carriersearch_nphy(pi, false);
	}

	wlapi_enable_mac(pi->sh->physhim);
}