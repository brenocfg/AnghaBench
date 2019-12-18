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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;
typedef  int s8 ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RADIO_MIMO_CORESEL_ALLRX ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_rssisel_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

int
wlc_phy_poll_rssi_nphy(struct brcms_phy *pi, u8 rssi_type, s32 *rssi_buf,
		       u8 nsamps)
{
	s16 rssi0, rssi1;
	u16 afectrlCore1_save = 0;
	u16 afectrlCore2_save = 0;
	u16 afectrlOverride1_save = 0;
	u16 afectrlOverride2_save = 0;
	u16 rfctrlOverrideAux0_save = 0;
	u16 rfctrlOverrideAux1_save = 0;
	u16 rfctrlMiscReg1_save = 0;
	u16 rfctrlMiscReg2_save = 0;
	u16 rfctrlcmd_save = 0;
	u16 rfctrloverride_save = 0;
	u16 rfctrlrssiothers1_save = 0;
	u16 rfctrlrssiothers2_save = 0;
	s8 tmp_buf[4];
	u8 ctr = 0, samp = 0;
	s32 rssi_out_val;
	u16 gpiosel_orig;

	afectrlCore1_save = read_phy_reg(pi, 0xa6);
	afectrlCore2_save = read_phy_reg(pi, 0xa7);
	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		rfctrlMiscReg1_save = read_phy_reg(pi, 0xf9);
		rfctrlMiscReg2_save = read_phy_reg(pi, 0xfb);
		afectrlOverride1_save = read_phy_reg(pi, 0x8f);
		afectrlOverride2_save = read_phy_reg(pi, 0xa5);
		rfctrlOverrideAux0_save = read_phy_reg(pi, 0xe5);
		rfctrlOverrideAux1_save = read_phy_reg(pi, 0xe6);
	} else {
		afectrlOverride1_save = read_phy_reg(pi, 0xa5);
		rfctrlcmd_save = read_phy_reg(pi, 0x78);
		rfctrloverride_save = read_phy_reg(pi, 0xec);
		rfctrlrssiothers1_save = read_phy_reg(pi, 0x7a);
		rfctrlrssiothers2_save = read_phy_reg(pi, 0x7d);
	}

	wlc_phy_rssisel_nphy(pi, RADIO_MIMO_CORESEL_ALLRX, rssi_type);

	gpiosel_orig = read_phy_reg(pi, 0xca);
	if (NREV_LT(pi->pubpi.phy_rev, 2))
		write_phy_reg(pi, 0xca, 5);

	for (ctr = 0; ctr < 4; ctr++)
		rssi_buf[ctr] = 0;

	for (samp = 0; samp < nsamps; samp++) {
		if (NREV_LT(pi->pubpi.phy_rev, 2)) {
			rssi0 = read_phy_reg(pi, 0x1c9);
			rssi1 = read_phy_reg(pi, 0x1ca);
		} else {
			rssi0 = read_phy_reg(pi, 0x219);
			rssi1 = read_phy_reg(pi, 0x21a);
		}

		ctr = 0;
		tmp_buf[ctr++] = ((s8) ((rssi0 & 0x3f) << 2)) >> 2;
		tmp_buf[ctr++] = ((s8) (((rssi0 >> 8) & 0x3f) << 2)) >> 2;
		tmp_buf[ctr++] = ((s8) ((rssi1 & 0x3f) << 2)) >> 2;
		tmp_buf[ctr++] = ((s8) (((rssi1 >> 8) & 0x3f) << 2)) >> 2;

		for (ctr = 0; ctr < 4; ctr++)
			rssi_buf[ctr] += tmp_buf[ctr];

	}

	rssi_out_val = rssi_buf[3] & 0xff;
	rssi_out_val |= (rssi_buf[2] & 0xff) << 8;
	rssi_out_val |= (rssi_buf[1] & 0xff) << 16;
	rssi_out_val |= (rssi_buf[0] & 0xff) << 24;

	if (NREV_LT(pi->pubpi.phy_rev, 2))
		write_phy_reg(pi, 0xca, gpiosel_orig);

	write_phy_reg(pi, 0xa6, afectrlCore1_save);
	write_phy_reg(pi, 0xa7, afectrlCore2_save);
	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		write_phy_reg(pi, 0xf9, rfctrlMiscReg1_save);
		write_phy_reg(pi, 0xfb, rfctrlMiscReg2_save);
		write_phy_reg(pi, 0x8f, afectrlOverride1_save);
		write_phy_reg(pi, 0xa5, afectrlOverride2_save);
		write_phy_reg(pi, 0xe5, rfctrlOverrideAux0_save);
		write_phy_reg(pi, 0xe6, rfctrlOverrideAux1_save);
	} else {
		write_phy_reg(pi, 0xa5, afectrlOverride1_save);
		write_phy_reg(pi, 0x78, rfctrlcmd_save);
		write_phy_reg(pi, 0xec, rfctrloverride_save);
		write_phy_reg(pi, 0x7a, rfctrlrssiothers1_save);
		write_phy_reg(pi, 0x7d, rfctrlrssiothers2_save);
	}

	return rssi_out_val;
}