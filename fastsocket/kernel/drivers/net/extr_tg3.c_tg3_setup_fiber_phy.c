#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {scalar_t__ active_flowctrl; scalar_t__ active_speed; scalar_t__ active_duplex; scalar_t__ autoneg; scalar_t__ rmt_adv; } ;
struct tg3 {int mac_mode; scalar_t__ phy_id; scalar_t__ serdes_counter; int led_ctrl; TYPE_3__ link_config; TYPE_2__* napi; scalar_t__ link_up; } ;
struct TYPE_5__ {TYPE_1__* hw_status; } ;
struct TYPE_4__ {int status; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  HW_AUTONEG ; 
 int /*<<< orphan*/  INIT_COMPLETE ; 
 int LED_CTRL_1000MBPS_ON ; 
 int LED_CTRL_LNKLED_OVERRIDE ; 
 int LED_CTRL_TRAFFIC_OVERRIDE ; 
 int /*<<< orphan*/  MAC_EVENT ; 
 scalar_t__ MAC_EVENT_LNKSTATE_CHANGED ; 
 int /*<<< orphan*/  MAC_LED_CTRL ; 
 int /*<<< orphan*/  MAC_MODE ; 
 int MAC_MODE_HALF_DUPLEX ; 
 int MAC_MODE_PORT_MODE_MASK ; 
 int MAC_MODE_PORT_MODE_TBI ; 
 scalar_t__ MAC_MODE_SEND_CONFIGS ; 
 int /*<<< orphan*/  MAC_STATUS ; 
 scalar_t__ MAC_STATUS_CFG_CHANGED ; 
 scalar_t__ MAC_STATUS_LNKSTATE_CHANGED ; 
 scalar_t__ MAC_STATUS_PCS_SYNCED ; 
 scalar_t__ MAC_STATUS_RCVD_CFG ; 
 scalar_t__ MAC_STATUS_SIGNAL_DET ; 
 scalar_t__ MAC_STATUS_SYNC_CHANGED ; 
 int /*<<< orphan*/  MAC_TX_AUTO_NEG ; 
 int SD_STATUS_LINK_CHG ; 
 int SD_STATUS_UPDATED ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_UNKNOWN ; 
 scalar_t__ TG3_PHY_ID_BCM8002 ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_init_bcm8002 (struct tg3*) ; 
 int /*<<< orphan*/  tg3_link_report (struct tg3*) ; 
 int tg3_setup_fiber_by_hand (struct tg3*,scalar_t__) ; 
 int tg3_setup_fiber_hw_autoneg (struct tg3*,scalar_t__) ; 
 int /*<<< orphan*/  tg3_test_and_report_link_chg (struct tg3*,int) ; 
 scalar_t__ tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tg3_setup_fiber_phy(struct tg3 *tp, bool force_reset)
{
	u32 orig_pause_cfg;
	u16 orig_active_speed;
	u8 orig_active_duplex;
	u32 mac_status;
	bool current_link_up;
	int i;

	orig_pause_cfg = tp->link_config.active_flowctrl;
	orig_active_speed = tp->link_config.active_speed;
	orig_active_duplex = tp->link_config.active_duplex;

	if (!tg3_flag(tp, HW_AUTONEG) &&
	    tp->link_up &&
	    tg3_flag(tp, INIT_COMPLETE)) {
		mac_status = tr32(MAC_STATUS);
		mac_status &= (MAC_STATUS_PCS_SYNCED |
			       MAC_STATUS_SIGNAL_DET |
			       MAC_STATUS_CFG_CHANGED |
			       MAC_STATUS_RCVD_CFG);
		if (mac_status == (MAC_STATUS_PCS_SYNCED |
				   MAC_STATUS_SIGNAL_DET)) {
			tw32_f(MAC_STATUS, (MAC_STATUS_SYNC_CHANGED |
					    MAC_STATUS_CFG_CHANGED));
			return 0;
		}
	}

	tw32_f(MAC_TX_AUTO_NEG, 0);

	tp->mac_mode &= ~(MAC_MODE_PORT_MODE_MASK | MAC_MODE_HALF_DUPLEX);
	tp->mac_mode |= MAC_MODE_PORT_MODE_TBI;
	tw32_f(MAC_MODE, tp->mac_mode);
	udelay(40);

	if (tp->phy_id == TG3_PHY_ID_BCM8002)
		tg3_init_bcm8002(tp);

	/* Enable link change event even when serdes polling.  */
	tw32_f(MAC_EVENT, MAC_EVENT_LNKSTATE_CHANGED);
	udelay(40);

	current_link_up = false;
	tp->link_config.rmt_adv = 0;
	mac_status = tr32(MAC_STATUS);

	if (tg3_flag(tp, HW_AUTONEG))
		current_link_up = tg3_setup_fiber_hw_autoneg(tp, mac_status);
	else
		current_link_up = tg3_setup_fiber_by_hand(tp, mac_status);

	tp->napi[0].hw_status->status =
		(SD_STATUS_UPDATED |
		 (tp->napi[0].hw_status->status & ~SD_STATUS_LINK_CHG));

	for (i = 0; i < 100; i++) {
		tw32_f(MAC_STATUS, (MAC_STATUS_SYNC_CHANGED |
				    MAC_STATUS_CFG_CHANGED));
		udelay(5);
		if ((tr32(MAC_STATUS) & (MAC_STATUS_SYNC_CHANGED |
					 MAC_STATUS_CFG_CHANGED |
					 MAC_STATUS_LNKSTATE_CHANGED)) == 0)
			break;
	}

	mac_status = tr32(MAC_STATUS);
	if ((mac_status & MAC_STATUS_PCS_SYNCED) == 0) {
		current_link_up = false;
		if (tp->link_config.autoneg == AUTONEG_ENABLE &&
		    tp->serdes_counter == 0) {
			tw32_f(MAC_MODE, (tp->mac_mode |
					  MAC_MODE_SEND_CONFIGS));
			udelay(1);
			tw32_f(MAC_MODE, tp->mac_mode);
		}
	}

	if (current_link_up) {
		tp->link_config.active_speed = SPEED_1000;
		tp->link_config.active_duplex = DUPLEX_FULL;
		tw32(MAC_LED_CTRL, (tp->led_ctrl |
				    LED_CTRL_LNKLED_OVERRIDE |
				    LED_CTRL_1000MBPS_ON));
	} else {
		tp->link_config.active_speed = SPEED_UNKNOWN;
		tp->link_config.active_duplex = DUPLEX_UNKNOWN;
		tw32(MAC_LED_CTRL, (tp->led_ctrl |
				    LED_CTRL_LNKLED_OVERRIDE |
				    LED_CTRL_TRAFFIC_OVERRIDE));
	}

	if (!tg3_test_and_report_link_chg(tp, current_link_up)) {
		u32 now_pause_cfg = tp->link_config.active_flowctrl;
		if (orig_pause_cfg != now_pause_cfg ||
		    orig_active_speed != tp->link_config.active_speed ||
		    orig_active_duplex != tp->link_config.active_duplex)
			tg3_link_report(tp);
	}

	return 0;
}