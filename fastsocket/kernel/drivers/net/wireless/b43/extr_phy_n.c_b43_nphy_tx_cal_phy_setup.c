#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {int rev; TYPE_1__* n; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_2__ phy; } ;
struct TYPE_3__ {int* tx_rx_cal_phy_saveregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_AFECTL_C1 ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_C2 ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_OVER ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_OVER1 ; 
 int /*<<< orphan*/  B43_NPHY_BBCFG ; 
 int B43_NPHY_BBCFG_RSTRX ; 
 int /*<<< orphan*/  B43_NPHY_PAPD_EN0 ; 
 int /*<<< orphan*/  B43_NPHY_PAPD_EN1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC2 ; 
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  N_INTC_OVERRIDE_PA ; 
 int /*<<< orphan*/  N_INTC_OVERRIDE_TRSW ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_rf_ctl_intc_override (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_ntab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_ntab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_nphy_tx_cal_phy_setup(struct b43_wldev *dev)
{
	u16 *regs = dev->phy.n->tx_rx_cal_phy_saveregs;
	u16 tmp;

	regs[0] = b43_phy_read(dev, B43_NPHY_AFECTL_C1);
	regs[1] = b43_phy_read(dev, B43_NPHY_AFECTL_C2);
	if (dev->phy.rev >= 3) {
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C1, 0xF0FF, 0x0A00);
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C2, 0xF0FF, 0x0A00);

		tmp = b43_phy_read(dev, B43_NPHY_AFECTL_OVER1);
		regs[2] = tmp;
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER1, tmp | 0x0600);

		tmp = b43_phy_read(dev, B43_NPHY_AFECTL_OVER);
		regs[3] = tmp;
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER, tmp | 0x0600);

		regs[4] = b43_phy_read(dev, B43_NPHY_BBCFG);
		b43_phy_mask(dev, B43_NPHY_BBCFG,
			     ~B43_NPHY_BBCFG_RSTRX & 0xFFFF);

		tmp = b43_ntab_read(dev, B43_NTAB16(8, 3));
		regs[5] = tmp;
		b43_ntab_write(dev, B43_NTAB16(8, 3), 0);

		tmp = b43_ntab_read(dev, B43_NTAB16(8, 19));
		regs[6] = tmp;
		b43_ntab_write(dev, B43_NTAB16(8, 19), 0);
		regs[7] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC1);
		regs[8] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC2);

		b43_nphy_rf_ctl_intc_override(dev, N_INTC_OVERRIDE_PA, 1, 3);
		b43_nphy_rf_ctl_intc_override(dev, N_INTC_OVERRIDE_TRSW, 2, 1);
		b43_nphy_rf_ctl_intc_override(dev, N_INTC_OVERRIDE_TRSW, 8, 2);

		regs[9] = b43_phy_read(dev, B43_NPHY_PAPD_EN0);
		regs[10] = b43_phy_read(dev, B43_NPHY_PAPD_EN1);
		b43_phy_mask(dev, B43_NPHY_PAPD_EN0, ~0x0001);
		b43_phy_mask(dev, B43_NPHY_PAPD_EN1, ~0x0001);
	} else {
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C1, 0x0FFF, 0xA000);
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C2, 0x0FFF, 0xA000);
		tmp = b43_phy_read(dev, B43_NPHY_AFECTL_OVER);
		regs[2] = tmp;
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER, tmp | 0x3000);
		tmp = b43_ntab_read(dev, B43_NTAB16(8, 2));
		regs[3] = tmp;
		tmp |= 0x2000;
		b43_ntab_write(dev, B43_NTAB16(8, 2), tmp);
		tmp = b43_ntab_read(dev, B43_NTAB16(8, 18));
		regs[4] = tmp;
		tmp |= 0x2000;
		b43_ntab_write(dev, B43_NTAB16(8, 18), tmp);
		regs[5] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC1);
		regs[6] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC2);
		if (b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ)
			tmp = 0x0180;
		else
			tmp = 0x0120;
		b43_phy_write(dev, B43_NPHY_RFCTL_INTC1, tmp);
		b43_phy_write(dev, B43_NPHY_RFCTL_INTC2, tmp);
	}
}