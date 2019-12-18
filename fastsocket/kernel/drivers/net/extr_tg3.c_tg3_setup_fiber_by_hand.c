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
struct TYPE_2__ {scalar_t__ autoneg; int /*<<< orphan*/  rmt_adv; } ;
struct tg3 {int mac_mode; TYPE_1__ link_config; } ;

/* Variables and functions */
 int ADVERTISE_1000XPAUSE ; 
 int ADVERTISE_1000XPSE_ASYM ; 
 int ANEG_CFG_PS1 ; 
 int ANEG_CFG_PS2 ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int LPA_1000XPAUSE ; 
 int LPA_1000XPAUSE_ASYM ; 
 int /*<<< orphan*/  MAC_MODE ; 
 int MAC_MODE_SEND_CONFIGS ; 
 int /*<<< orphan*/  MAC_STATUS ; 
 int MAC_STATUS_CFG_CHANGED ; 
 int MAC_STATUS_PCS_SYNCED ; 
 int MAC_STATUS_RCVD_CFG ; 
 int MAC_STATUS_SYNC_CHANGED ; 
 int MR_LP_ADV_ASYM_PAUSE ; 
 int MR_LP_ADV_SYM_PAUSE ; 
 scalar_t__ fiber_autoneg (struct tg3*,int*,int*) ; 
 int /*<<< orphan*/  mii_adv_to_ethtool_adv_x (int) ; 
 int /*<<< orphan*/  tg3_setup_flow_control (struct tg3*,int,int) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool tg3_setup_fiber_by_hand(struct tg3 *tp, u32 mac_status)
{
	bool current_link_up = false;

	if (!(mac_status & MAC_STATUS_PCS_SYNCED))
		goto out;

	if (tp->link_config.autoneg == AUTONEG_ENABLE) {
		u32 txflags, rxflags;
		int i;

		if (fiber_autoneg(tp, &txflags, &rxflags)) {
			u32 local_adv = 0, remote_adv = 0;

			if (txflags & ANEG_CFG_PS1)
				local_adv |= ADVERTISE_1000XPAUSE;
			if (txflags & ANEG_CFG_PS2)
				local_adv |= ADVERTISE_1000XPSE_ASYM;

			if (rxflags & MR_LP_ADV_SYM_PAUSE)
				remote_adv |= LPA_1000XPAUSE;
			if (rxflags & MR_LP_ADV_ASYM_PAUSE)
				remote_adv |= LPA_1000XPAUSE_ASYM;

			tp->link_config.rmt_adv =
					   mii_adv_to_ethtool_adv_x(remote_adv);

			tg3_setup_flow_control(tp, local_adv, remote_adv);

			current_link_up = true;
		}
		for (i = 0; i < 30; i++) {
			udelay(20);
			tw32_f(MAC_STATUS,
			       (MAC_STATUS_SYNC_CHANGED |
				MAC_STATUS_CFG_CHANGED));
			udelay(40);
			if ((tr32(MAC_STATUS) &
			     (MAC_STATUS_SYNC_CHANGED |
			      MAC_STATUS_CFG_CHANGED)) == 0)
				break;
		}

		mac_status = tr32(MAC_STATUS);
		if (!current_link_up &&
		    (mac_status & MAC_STATUS_PCS_SYNCED) &&
		    !(mac_status & MAC_STATUS_RCVD_CFG))
			current_link_up = true;
	} else {
		tg3_setup_flow_control(tp, 0, 0);

		/* Forcing 1000FD link up. */
		current_link_up = true;

		tw32_f(MAC_MODE, (tp->mac_mode | MAC_MODE_SEND_CONFIGS));
		udelay(40);

		tw32_f(MAC_MODE, tp->mac_mode);
		udelay(40);
	}

out:
	return current_link_up;
}