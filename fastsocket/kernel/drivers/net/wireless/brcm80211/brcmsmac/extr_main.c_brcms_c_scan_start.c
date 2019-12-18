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
struct brcms_c_info {TYPE_1__* band; } ;
struct TYPE_2__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_HOLD_FOR_SCAN ; 
 int /*<<< orphan*/  wlc_phy_hold_upd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void brcms_c_scan_start(struct brcms_c_info *wlc)
{
	wlc_phy_hold_upd(wlc->band->pi, PHY_HOLD_FOR_SCAN, true);
}