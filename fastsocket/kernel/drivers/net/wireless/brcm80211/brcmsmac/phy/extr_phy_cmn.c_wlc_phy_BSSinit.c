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
typedef  size_t uint ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {scalar_t__ nphy_noise_index; int /*<<< orphan*/ ** nphy_noise_win; TYPE_1__* sh; } ;
typedef  scalar_t__ s8 ;
struct TYPE_2__ {scalar_t__ phy_noise_index; scalar_t__* phy_noise_window; } ;

/* Variables and functions */
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 size_t MA_WINDOW_SZ ; 
 scalar_t__ PHY_NOISE_FIXED_VAL_LCNPHY ; 
 int /*<<< orphan*/  PHY_NOISE_FIXED_VAL_NPHY ; 
 size_t PHY_NOISE_WINDOW_SZ ; 
 size_t WL_ANT_IDX_1 ; 
 size_t WL_ANT_RX_MAX ; 

void wlc_phy_BSSinit(struct brcms_phy_pub *pih, bool bonlyap, int rssi)
{
	struct brcms_phy *pi = (struct brcms_phy *) pih;
	uint i;
	uint k;

	for (i = 0; i < MA_WINDOW_SZ; i++)
		pi->sh->phy_noise_window[i] = (s8) (rssi & 0xff);
	if (ISLCNPHY(pi)) {
		for (i = 0; i < MA_WINDOW_SZ; i++)
			pi->sh->phy_noise_window[i] =
				PHY_NOISE_FIXED_VAL_LCNPHY;
	}
	pi->sh->phy_noise_index = 0;

	for (i = 0; i < PHY_NOISE_WINDOW_SZ; i++) {
		for (k = WL_ANT_IDX_1; k < WL_ANT_RX_MAX; k++)
			pi->nphy_noise_win[k][i] = PHY_NOISE_FIXED_VAL_NPHY;
	}
	pi->nphy_noise_index = 0;
}