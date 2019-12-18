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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlc_phy_rxcal_gainctrl_nphy_rev5 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wlc_phy_rxcal_gainctrl_nphy(struct brcms_phy *pi, u8 rx_core, u16 *rxgain,
			    u8 cal_type)
{
	wlc_phy_rxcal_gainctrl_nphy_rev5(pi, rx_core, rxgain, cal_type);
}