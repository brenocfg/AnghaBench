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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_4__ {TYPE_1__* lcn; } ;
struct b43_wldev {TYPE_2__ phy; } ;
typedef  enum lcn_sense_type { ____Placeholder_lcn_sense_type } lcn_sense_type ;
struct TYPE_3__ {int tx_pwr_curr_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LCNTAB16 (int,int) ; 
#define  B43_SENSE_TEMP 129 
#define  B43_SENSE_VBAT 128 
 int /*<<< orphan*/  b43_dummy_transmission (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_lcntab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_mac_enable (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_mac_suspend (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int b43_radio_read (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_phy_lcn_sense_setup(struct b43_wldev *dev,
				    enum lcn_sense_type sense_type)
{
	u8 auxpga_vmidcourse, auxpga_vmidfine, auxpga_gain;
	u16 auxpga_vmid;
	u8 tx_pwr_idx;
	u8 i;

	u16 save_radio_regs[6][2] = {
		{ 0x007, 0 }, { 0x0ff, 0 }, { 0x11f, 0 }, { 0x005, 0 },
		{ 0x025, 0 }, { 0x112, 0 },
	};
	u16 save_phy_regs[14][2] = {
		{ 0x503, 0 }, { 0x4a4, 0 }, { 0x4d0, 0 }, { 0x4d9, 0 },
		{ 0x4da, 0 }, { 0x4a6, 0 }, { 0x938, 0 }, { 0x939, 0 },
		{ 0x4d8, 0 }, { 0x4d0, 0 }, { 0x4d7, 0 }, { 0x4a5, 0 },
		{ 0x40d, 0 }, { 0x4a2, 0 },
	};
	u16 save_radio_4a4;

	msleep(1);

	/* Save */
	for (i = 0; i < 6; i++)
		save_radio_regs[i][1] = b43_radio_read(dev,
						       save_radio_regs[i][0]);
	for (i = 0; i < 14; i++)
		save_phy_regs[i][1] = b43_phy_read(dev, save_phy_regs[i][0]);
	b43_mac_suspend(dev);
	save_radio_4a4 = b43_radio_read(dev, 0x4a4);
	/* wlc_lcnphy_set_tx_pwr_ctrl(pi, LCNPHY_TX_PWR_CTRL_OFF); */
	tx_pwr_idx = dev->phy.lcn->tx_pwr_curr_idx;

	/* Setup */
	/* TODO: wlc_lcnphy_set_tx_pwr_by_index(pi, 127); */
	b43_radio_set(dev, 0x007, 0x1);
	b43_radio_set(dev, 0x0ff, 0x10);
	b43_radio_set(dev, 0x11f, 0x4);

	b43_phy_mask(dev, 0x503, ~0x1);
	b43_phy_mask(dev, 0x503, ~0x4);
	b43_phy_mask(dev, 0x4a4, ~0x4000);
	b43_phy_mask(dev, 0x4a4, (u16) ~0x8000);
	b43_phy_mask(dev, 0x4d0, ~0x20);
	b43_phy_set(dev, 0x4a5, 0xff);
	b43_phy_maskset(dev, 0x4a5, ~0x7000, 0x5000);
	b43_phy_mask(dev, 0x4a5, ~0x700);
	b43_phy_maskset(dev, 0x40d, ~0xff, 64);
	b43_phy_maskset(dev, 0x40d, ~0x700, 0x600);
	b43_phy_maskset(dev, 0x4a2, ~0xff, 64);
	b43_phy_maskset(dev, 0x4a2, ~0x700, 0x600);
	b43_phy_maskset(dev, 0x4d9, ~0x70, 0x20);
	b43_phy_maskset(dev, 0x4d9, ~0x700, 0x300);
	b43_phy_maskset(dev, 0x4d9, ~0x7000, 0x1000);
	b43_phy_mask(dev, 0x4da, ~0x1000);
	b43_phy_set(dev, 0x4da, 0x2000);
	b43_phy_set(dev, 0x4a6, 0x8000);

	b43_radio_write(dev, 0x025, 0xc);
	b43_radio_set(dev, 0x005, 0x8);
	b43_phy_set(dev, 0x938, 0x4);
	b43_phy_set(dev, 0x939, 0x4);
	b43_phy_set(dev, 0x4a4, 0x1000);

	/* FIXME: don't hardcode */
	b43_lcntab_write(dev, B43_LCNTAB16(0x8, 0x6), 0x640);

	switch (sense_type) {
	case B43_SENSE_TEMP:
		b43_phy_set(dev, 0x4d7, 0x8);
		b43_phy_maskset(dev, 0x4d7, ~0x7000, 0x1000);
		auxpga_vmidcourse = 8;
		auxpga_vmidfine = 0x4;
		auxpga_gain = 2;
		b43_radio_set(dev, 0x082, 0x20);
		break;
	case B43_SENSE_VBAT:
		b43_phy_set(dev, 0x4d7, 0x8);
		b43_phy_maskset(dev, 0x4d7, ~0x7000, 0x3000);
		auxpga_vmidcourse = 7;
		auxpga_vmidfine = 0xa;
		auxpga_gain = 2;
		break;
	}
	auxpga_vmid = (0x200 | (auxpga_vmidcourse << 4) | auxpga_vmidfine);

	b43_phy_set(dev, 0x4d8, 0x1);
	b43_phy_maskset(dev, 0x4d8, ~(0x3ff << 2), auxpga_vmid << 2);
	b43_phy_set(dev, 0x4d8, 0x2);
	b43_phy_maskset(dev, 0x4d8, ~(0x7 << 12), auxpga_gain << 12);
	b43_phy_set(dev, 0x4d0, 0x20);
	b43_radio_write(dev, 0x112, 0x6);

	b43_dummy_transmission(dev, true, false);
	/* Wait if not done */
	if (!(b43_phy_read(dev, 0x476) & 0x8000))
		udelay(10);

	/* Restore */
	for (i = 0; i < 6; i++)
		b43_radio_write(dev, save_radio_regs[i][0],
				save_radio_regs[i][1]);
	for (i = 0; i < 14; i++)
		b43_phy_write(dev, save_phy_regs[i][0], save_phy_regs[i][1]);
	/* TODO: wlc_lcnphy_set_tx_pwr_by_index(tx_pwr_idx) */
	b43_radio_write(dev, 0x4a4, save_radio_4a4);

	b43_mac_enable(dev);

	msleep(1);
}