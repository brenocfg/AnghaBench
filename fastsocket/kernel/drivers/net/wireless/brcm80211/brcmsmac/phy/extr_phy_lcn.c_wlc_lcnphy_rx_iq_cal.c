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
typedef  int u32 ;
typedef  int u16 ;
struct lcnphy_txgains {int dummy; } ;
struct lcnphy_rx_iqcomp {scalar_t__ chan; scalar_t__ b; scalar_t__ a; } ;
struct brcms_phy_lcnphy {int lcnphy_current_index; } ;
struct TYPE_2__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 scalar_t__ CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int LCNPHY_TX_PWR_CTRL_OFF ; 
 int /*<<< orphan*/  RADIO_2064_REG00B ; 
 int /*<<< orphan*/  RADIO_2064_REG01D ; 
 int /*<<< orphan*/  RADIO_2064_REG02E ; 
 int /*<<< orphan*/  RADIO_2064_REG06A ; 
 int /*<<< orphan*/  RADIO_2064_REG098 ; 
 int /*<<< orphan*/  RADIO_2064_REG113 ; 
 int /*<<< orphan*/  RADIO_2064_REG114 ; 
 int /*<<< orphan*/  RADIO_2064_REG116 ; 
 int /*<<< orphan*/  RADIO_2064_REG12A ; 
 int /*<<< orphan*/  RADIO_2064_REG12C ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int read_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rxiq_cal_rf_reg ; 
 int /*<<< orphan*/  udelay (int) ; 
 int wlc_lcnphy_calc_rx_iq_comp (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_clear_trsw_override (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_disable_tx_gain_override (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_get_tx_gain (struct brcms_phy*,struct lcnphy_txgains*) ; 
 int wlc_lcnphy_get_tx_pwr_ctrl (struct brcms_phy*) ; 
 int wlc_lcnphy_measure_digital_power (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_rx_gain_override_enable (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_rx_gain_by_distribution (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_rx_iq_comp (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_trsw_override (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_by_index (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_ctrl (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_start_tx_tone (struct brcms_phy*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_stop_tx_tone (struct brcms_phy*) ; 
 int wlc_lcnphy_tx_gain_override_enabled (struct brcms_phy*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
wlc_lcnphy_rx_iq_cal(struct brcms_phy *pi,
		     const struct lcnphy_rx_iqcomp *iqcomp,
		     int iqcomp_sz, bool tx_switch, bool rx_switch, int module,
		     int tx_gain_idx)
{
	struct lcnphy_txgains old_gains;
	u16 tx_pwr_ctrl;
	u8 tx_gain_index_old = 0;
	bool result = false, tx_gain_override_old = false;
	u16 i, Core1TxControl_old, RFOverride0_old,
	    RFOverrideVal0_old, rfoverride2_old, rfoverride2val_old,
	    rfoverride3_old, rfoverride3val_old, rfoverride4_old,
	    rfoverride4val_old, afectrlovr_old, afectrlovrval_old;
	int tia_gain;
	u32 received_power, rx_pwr_threshold;
	u16 old_sslpnCalibClkEnCtrl, old_sslpnRxFeClkEnCtrl;
	u16 values_to_save[11];
	s16 *ptr;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	ptr = kmalloc(sizeof(s16) * 131, GFP_ATOMIC);
	if (NULL == ptr)
		return false;
	if (module == 2) {
		while (iqcomp_sz--) {
			if (iqcomp[iqcomp_sz].chan ==
			    CHSPEC_CHANNEL(pi->radio_chanspec)) {
				wlc_lcnphy_set_rx_iq_comp(pi,
							  (u16)
							  iqcomp[iqcomp_sz].a,
							  (u16)
							  iqcomp[iqcomp_sz].b);
				result = true;
				break;
			}
		}
		goto cal_done;
	}

	if (module == 1) {

		tx_pwr_ctrl = wlc_lcnphy_get_tx_pwr_ctrl(pi);
		wlc_lcnphy_set_tx_pwr_ctrl(pi, LCNPHY_TX_PWR_CTRL_OFF);

		for (i = 0; i < 11; i++)
			values_to_save[i] =
				read_radio_reg(pi, rxiq_cal_rf_reg[i]);
		Core1TxControl_old = read_phy_reg(pi, 0x631);

		or_phy_reg(pi, 0x631, 0x0015);

		RFOverride0_old = read_phy_reg(pi, 0x44c);
		RFOverrideVal0_old = read_phy_reg(pi, 0x44d);
		rfoverride2_old = read_phy_reg(pi, 0x4b0);
		rfoverride2val_old = read_phy_reg(pi, 0x4b1);
		rfoverride3_old = read_phy_reg(pi, 0x4f9);
		rfoverride3val_old = read_phy_reg(pi, 0x4fa);
		rfoverride4_old = read_phy_reg(pi, 0x938);
		rfoverride4val_old = read_phy_reg(pi, 0x939);
		afectrlovr_old = read_phy_reg(pi, 0x43b);
		afectrlovrval_old = read_phy_reg(pi, 0x43c);
		old_sslpnCalibClkEnCtrl = read_phy_reg(pi, 0x6da);
		old_sslpnRxFeClkEnCtrl = read_phy_reg(pi, 0x6db);

		tx_gain_override_old = wlc_lcnphy_tx_gain_override_enabled(pi);
		if (tx_gain_override_old) {
			wlc_lcnphy_get_tx_gain(pi, &old_gains);
			tx_gain_index_old = pi_lcn->lcnphy_current_index;
		}

		wlc_lcnphy_set_tx_pwr_by_index(pi, tx_gain_idx);

		mod_phy_reg(pi, 0x4f9, (0x1 << 0), 1 << 0);
		mod_phy_reg(pi, 0x4fa, (0x1 << 0), 0 << 0);

		mod_phy_reg(pi, 0x43b, (0x1 << 1), 1 << 1);
		mod_phy_reg(pi, 0x43c, (0x1 << 1), 0 << 1);

		write_radio_reg(pi, RADIO_2064_REG116, 0x06);
		write_radio_reg(pi, RADIO_2064_REG12C, 0x07);
		write_radio_reg(pi, RADIO_2064_REG06A, 0xd3);
		write_radio_reg(pi, RADIO_2064_REG098, 0x03);
		write_radio_reg(pi, RADIO_2064_REG00B, 0x7);
		mod_radio_reg(pi, RADIO_2064_REG113, 1 << 4, 1 << 4);
		write_radio_reg(pi, RADIO_2064_REG01D, 0x01);
		write_radio_reg(pi, RADIO_2064_REG114, 0x01);
		write_radio_reg(pi, RADIO_2064_REG02E, 0x10);
		write_radio_reg(pi, RADIO_2064_REG12A, 0x08);

		mod_phy_reg(pi, 0x938, (0x1 << 0), 1 << 0);
		mod_phy_reg(pi, 0x939, (0x1 << 0), 0 << 0);
		mod_phy_reg(pi, 0x938, (0x1 << 1), 1 << 1);
		mod_phy_reg(pi, 0x939, (0x1 << 1), 1 << 1);
		mod_phy_reg(pi, 0x938, (0x1 << 2), 1 << 2);
		mod_phy_reg(pi, 0x939, (0x1 << 2), 1 << 2);
		mod_phy_reg(pi, 0x938, (0x1 << 3), 1 << 3);
		mod_phy_reg(pi, 0x939, (0x1 << 3), 1 << 3);
		mod_phy_reg(pi, 0x938, (0x1 << 5), 1 << 5);
		mod_phy_reg(pi, 0x939, (0x1 << 5), 0 << 5);

		mod_phy_reg(pi, 0x43b, (0x1 << 0), 1 << 0);
		mod_phy_reg(pi, 0x43c, (0x1 << 0), 0 << 0);

		wlc_lcnphy_start_tx_tone(pi, 2000, 120, 0);
		write_phy_reg(pi, 0x6da, 0xffff);
		or_phy_reg(pi, 0x6db, 0x3);
		wlc_lcnphy_set_trsw_override(pi, tx_switch, rx_switch);
		wlc_lcnphy_rx_gain_override_enable(pi, true);

		tia_gain = 8;
		rx_pwr_threshold = 950;
		while (tia_gain > 0) {
			tia_gain -= 1;
			wlc_lcnphy_set_rx_gain_by_distribution(pi,
							       0, 0, 2, 2,
							       (u16)
							       tia_gain, 1, 0);
			udelay(500);

			received_power =
				wlc_lcnphy_measure_digital_power(pi, 2000);
			if (received_power < rx_pwr_threshold)
				break;
		}
		result = wlc_lcnphy_calc_rx_iq_comp(pi, 0xffff);

		wlc_lcnphy_stop_tx_tone(pi);

		write_phy_reg(pi, 0x631, Core1TxControl_old);

		write_phy_reg(pi, 0x44c, RFOverrideVal0_old);
		write_phy_reg(pi, 0x44d, RFOverrideVal0_old);
		write_phy_reg(pi, 0x4b0, rfoverride2_old);
		write_phy_reg(pi, 0x4b1, rfoverride2val_old);
		write_phy_reg(pi, 0x4f9, rfoverride3_old);
		write_phy_reg(pi, 0x4fa, rfoverride3val_old);
		write_phy_reg(pi, 0x938, rfoverride4_old);
		write_phy_reg(pi, 0x939, rfoverride4val_old);
		write_phy_reg(pi, 0x43b, afectrlovr_old);
		write_phy_reg(pi, 0x43c, afectrlovrval_old);
		write_phy_reg(pi, 0x6da, old_sslpnCalibClkEnCtrl);
		write_phy_reg(pi, 0x6db, old_sslpnRxFeClkEnCtrl);

		wlc_lcnphy_clear_trsw_override(pi);

		mod_phy_reg(pi, 0x44c, (0x1 << 2), 0 << 2);

		for (i = 0; i < 11; i++)
			write_radio_reg(pi, rxiq_cal_rf_reg[i],
					values_to_save[i]);

		if (tx_gain_override_old)
			wlc_lcnphy_set_tx_pwr_by_index(pi, tx_gain_index_old);
		else
			wlc_lcnphy_disable_tx_gain_override(pi);

		wlc_lcnphy_set_tx_pwr_ctrl(pi, tx_pwr_ctrl);
		wlc_lcnphy_rx_gain_override_enable(pi, false);
	}

cal_done:
	kfree(ptr);
	return result;
}