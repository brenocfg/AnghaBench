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
typedef  scalar_t__ u8 ;
struct brcms_phy {int phynoise_state; scalar_t__ phynoise_chan_watchdog; TYPE_1__* sh; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_2__ {size_t phy_noise_index; int /*<<< orphan*/ * phy_noise_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_WINDOW_SZ ; 
 size_t MODINC (size_t,int /*<<< orphan*/ ) ; 
 int PHY_NOISE_STATE_EXTERNAL ; 
 int PHY_NOISE_STATE_MON ; 

__attribute__((used)) static void wlc_phy_noise_cb(struct brcms_phy *pi, u8 channel, s8 noise_dbm)
{
	if (!pi->phynoise_state)
		return;

	if (pi->phynoise_state & PHY_NOISE_STATE_MON) {
		if (pi->phynoise_chan_watchdog == channel) {
			pi->sh->phy_noise_window[pi->sh->phy_noise_index] =
				noise_dbm;
			pi->sh->phy_noise_index =
				MODINC(pi->sh->phy_noise_index, MA_WINDOW_SZ);
		}
		pi->phynoise_state &= ~PHY_NOISE_STATE_MON;
	}

	if (pi->phynoise_state & PHY_NOISE_STATE_EXTERNAL)
		pi->phynoise_state &= ~PHY_NOISE_STATE_EXTERNAL;

}