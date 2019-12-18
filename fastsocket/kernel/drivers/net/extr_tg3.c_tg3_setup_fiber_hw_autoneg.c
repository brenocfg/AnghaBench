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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ autoneg; int /*<<< orphan*/  rmt_adv; int /*<<< orphan*/  flowctrl; } ;
struct tg3 {int phy_flags; void* serdes_counter; TYPE_1__ link_config; } ;

/* Variables and functions */
 int ADVERTISE_1000XPAUSE ; 
 int ADVERTISE_1000XPSE_ASYM ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ CHIPREV_ID_5704_A0 ; 
 scalar_t__ CHIPREV_ID_5704_A1 ; 
 int DUAL_MAC_CTRL_ID ; 
 int LPA_1000XPAUSE ; 
 int LPA_1000XPAUSE_ASYM ; 
 int /*<<< orphan*/  MAC_SERDES_CFG ; 
 int /*<<< orphan*/  MAC_STATUS ; 
 int MAC_STATUS_PCS_SYNCED ; 
 int MAC_STATUS_RCVD_CFG ; 
 int MAC_STATUS_SIGNAL_DET ; 
 void* SERDES_AN_TIMEOUT_5704S ; 
 void* SERDES_PARALLEL_DET_TIMEOUT ; 
 int SG_DIG_ASYM_PAUSE ; 
 int SG_DIG_AUTONEG_COMPLETE ; 
 int SG_DIG_COMMON_SETUP ; 
 int /*<<< orphan*/  SG_DIG_CTRL ; 
 int SG_DIG_PARTNER_ASYM_PAUSE ; 
 int SG_DIG_PARTNER_PAUSE_CAPABLE ; 
 int SG_DIG_PAUSE_CAP ; 
 int SG_DIG_SOFT_RESET ; 
 int /*<<< orphan*/  SG_DIG_STATUS ; 
 int SG_DIG_USING_HW_AUTONEG ; 
 int /*<<< orphan*/  TG3PCI_DUAL_MAC_CTRL ; 
 int TG3_PHYFLG_PARALLEL_DETECT ; 
 int /*<<< orphan*/  mii_adv_to_ethtool_adv_x (int) ; 
 int tg3_advert_flowctrl_1000X (int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_chip_rev_id (struct tg3*) ; 
 int /*<<< orphan*/  tg3_setup_flow_control (struct tg3*,int,int) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool tg3_setup_fiber_hw_autoneg(struct tg3 *tp, u32 mac_status)
{
	u16 flowctrl;
	bool current_link_up;
	u32 sg_dig_ctrl, sg_dig_status;
	u32 serdes_cfg, expected_sg_dig_ctrl;
	int workaround, port_a;

	serdes_cfg = 0;
	expected_sg_dig_ctrl = 0;
	workaround = 0;
	port_a = 1;
	current_link_up = false;

	if (tg3_chip_rev_id(tp) != CHIPREV_ID_5704_A0 &&
	    tg3_chip_rev_id(tp) != CHIPREV_ID_5704_A1) {
		workaround = 1;
		if (tr32(TG3PCI_DUAL_MAC_CTRL) & DUAL_MAC_CTRL_ID)
			port_a = 0;

		/* preserve bits 0-11,13,14 for signal pre-emphasis */
		/* preserve bits 20-23 for voltage regulator */
		serdes_cfg = tr32(MAC_SERDES_CFG) & 0x00f06fff;
	}

	sg_dig_ctrl = tr32(SG_DIG_CTRL);

	if (tp->link_config.autoneg != AUTONEG_ENABLE) {
		if (sg_dig_ctrl & SG_DIG_USING_HW_AUTONEG) {
			if (workaround) {
				u32 val = serdes_cfg;

				if (port_a)
					val |= 0xc010000;
				else
					val |= 0x4010000;
				tw32_f(MAC_SERDES_CFG, val);
			}

			tw32_f(SG_DIG_CTRL, SG_DIG_COMMON_SETUP);
		}
		if (mac_status & MAC_STATUS_PCS_SYNCED) {
			tg3_setup_flow_control(tp, 0, 0);
			current_link_up = true;
		}
		goto out;
	}

	/* Want auto-negotiation.  */
	expected_sg_dig_ctrl = SG_DIG_USING_HW_AUTONEG | SG_DIG_COMMON_SETUP;

	flowctrl = tg3_advert_flowctrl_1000X(tp->link_config.flowctrl);
	if (flowctrl & ADVERTISE_1000XPAUSE)
		expected_sg_dig_ctrl |= SG_DIG_PAUSE_CAP;
	if (flowctrl & ADVERTISE_1000XPSE_ASYM)
		expected_sg_dig_ctrl |= SG_DIG_ASYM_PAUSE;

	if (sg_dig_ctrl != expected_sg_dig_ctrl) {
		if ((tp->phy_flags & TG3_PHYFLG_PARALLEL_DETECT) &&
		    tp->serdes_counter &&
		    ((mac_status & (MAC_STATUS_PCS_SYNCED |
				    MAC_STATUS_RCVD_CFG)) ==
		     MAC_STATUS_PCS_SYNCED)) {
			tp->serdes_counter--;
			current_link_up = true;
			goto out;
		}
restart_autoneg:
		if (workaround)
			tw32_f(MAC_SERDES_CFG, serdes_cfg | 0xc011000);
		tw32_f(SG_DIG_CTRL, expected_sg_dig_ctrl | SG_DIG_SOFT_RESET);
		udelay(5);
		tw32_f(SG_DIG_CTRL, expected_sg_dig_ctrl);

		tp->serdes_counter = SERDES_AN_TIMEOUT_5704S;
		tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;
	} else if (mac_status & (MAC_STATUS_PCS_SYNCED |
				 MAC_STATUS_SIGNAL_DET)) {
		sg_dig_status = tr32(SG_DIG_STATUS);
		mac_status = tr32(MAC_STATUS);

		if ((sg_dig_status & SG_DIG_AUTONEG_COMPLETE) &&
		    (mac_status & MAC_STATUS_PCS_SYNCED)) {
			u32 local_adv = 0, remote_adv = 0;

			if (sg_dig_ctrl & SG_DIG_PAUSE_CAP)
				local_adv |= ADVERTISE_1000XPAUSE;
			if (sg_dig_ctrl & SG_DIG_ASYM_PAUSE)
				local_adv |= ADVERTISE_1000XPSE_ASYM;

			if (sg_dig_status & SG_DIG_PARTNER_PAUSE_CAPABLE)
				remote_adv |= LPA_1000XPAUSE;
			if (sg_dig_status & SG_DIG_PARTNER_ASYM_PAUSE)
				remote_adv |= LPA_1000XPAUSE_ASYM;

			tp->link_config.rmt_adv =
					   mii_adv_to_ethtool_adv_x(remote_adv);

			tg3_setup_flow_control(tp, local_adv, remote_adv);
			current_link_up = true;
			tp->serdes_counter = 0;
			tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;
		} else if (!(sg_dig_status & SG_DIG_AUTONEG_COMPLETE)) {
			if (tp->serdes_counter)
				tp->serdes_counter--;
			else {
				if (workaround) {
					u32 val = serdes_cfg;

					if (port_a)
						val |= 0xc010000;
					else
						val |= 0x4010000;

					tw32_f(MAC_SERDES_CFG, val);
				}

				tw32_f(SG_DIG_CTRL, SG_DIG_COMMON_SETUP);
				udelay(40);

				/* Link parallel detection - link is up */
				/* only if we have PCS_SYNC and not */
				/* receiving config code words */
				mac_status = tr32(MAC_STATUS);
				if ((mac_status & MAC_STATUS_PCS_SYNCED) &&
				    !(mac_status & MAC_STATUS_RCVD_CFG)) {
					tg3_setup_flow_control(tp, 0, 0);
					current_link_up = true;
					tp->phy_flags |=
						TG3_PHYFLG_PARALLEL_DETECT;
					tp->serdes_counter =
						SERDES_PARALLEL_DET_TIMEOUT;
				} else
					goto restart_autoneg;
			}
		}
	} else {
		tp->serdes_counter = SERDES_AN_TIMEOUT_5704S;
		tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;
	}

out:
	return current_link_up;
}