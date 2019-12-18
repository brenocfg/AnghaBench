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
typedef  int u32 ;
struct lpphy_tx_gains {int pad; int gm; int pga; int dac; } ;
struct TYPE_2__ {int rev; struct b43_phy_lp* lp; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_lp {scalar_t__ txpctl_mode; scalar_t__ tx_pwr_idx_over; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_RF_PWR_OVERRIDE ; 
 scalar_t__ B43_LPPHY_TXPCTL_OFF ; 
 int /*<<< orphan*/  B43_LPPHY_TXPCTL_SW ; 
 int /*<<< orphan*/  B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL ; 
 int /*<<< orphan*/  B43_LPTAB16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  B43_LPTAB32 (int,scalar_t__) ; 
 int b43_lptab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_lptab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lpphy_enable_tx_gain_override (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_read_tx_pctl_mode_from_hardware (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_set_bb_mult (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_set_dac_gain (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_set_pa_gain (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_set_tx_gains (struct b43_wldev*,struct lpphy_tx_gains) ; 
 int /*<<< orphan*/  lpphy_set_tx_iqcc (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  lpphy_set_tx_power_control (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpphy_set_tx_power_by_index(struct b43_wldev *dev, u8 index)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;
	struct lpphy_tx_gains gains;
	u32 iq_comp, tx_gain, coeff, rf_power;

	lpphy->tx_pwr_idx_over = index;
	lpphy_read_tx_pctl_mode_from_hardware(dev);
	if (lpphy->txpctl_mode != B43_LPPHY_TXPCTL_OFF)
		lpphy_set_tx_power_control(dev, B43_LPPHY_TXPCTL_SW);
	if (dev->phy.rev >= 2) {
		iq_comp = b43_lptab_read(dev, B43_LPTAB32(7, index + 320));
		tx_gain = b43_lptab_read(dev, B43_LPTAB32(7, index + 192));
		gains.pad = (tx_gain >> 16) & 0xFF;
		gains.gm = tx_gain & 0xFF;
		gains.pga = (tx_gain >> 8) & 0xFF;
		gains.dac = (iq_comp >> 28) & 0xFF;
		lpphy_set_tx_gains(dev, gains);
	} else {
		iq_comp = b43_lptab_read(dev, B43_LPTAB32(10, index + 320));
		tx_gain = b43_lptab_read(dev, B43_LPTAB32(10, index + 192));
		b43_phy_maskset(dev, B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL,
				0xF800, (tx_gain >> 4) & 0x7FFF);
		lpphy_set_dac_gain(dev, tx_gain & 0x7);
		lpphy_set_pa_gain(dev, (tx_gain >> 24) & 0x7F);
	}
	lpphy_set_bb_mult(dev, (iq_comp >> 20) & 0xFF);
	lpphy_set_tx_iqcc(dev, (iq_comp >> 10) & 0x3FF, iq_comp & 0x3FF);
	if (dev->phy.rev >= 2) {
		coeff = b43_lptab_read(dev, B43_LPTAB32(7, index + 448));
	} else {
		coeff = b43_lptab_read(dev, B43_LPTAB32(10, index + 448));
	}
	b43_lptab_write(dev, B43_LPTAB16(0, 85), coeff & 0xFFFF);
	if (dev->phy.rev >= 2) {
		rf_power = b43_lptab_read(dev, B43_LPTAB32(7, index + 576));
		b43_phy_maskset(dev, B43_LPPHY_RF_PWR_OVERRIDE, 0xFF00,
				rf_power & 0xFFFF);//SPEC FIXME mask & set != 0
	}
	lpphy_enable_tx_gain_override(dev);
}