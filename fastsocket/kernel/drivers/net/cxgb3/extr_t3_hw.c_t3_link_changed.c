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
typedef  int u32 ;
struct link_config {int link_ok; int requested_fc; int speed; int duplex; int fc; scalar_t__ autoneg; } ;
struct TYPE_5__ {int /*<<< orphan*/  link_faults; } ;
struct cmac {scalar_t__ offset; TYPE_2__ stats; } ;
struct cphy {TYPE_1__* ops; } ;
struct port_info {int link_fault; struct link_config link_config; struct cmac mac; struct cphy phy; } ;
struct TYPE_6__ {scalar_t__ rev; } ;
struct adapter {TYPE_3__ params; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_link_status ) (struct cphy*,int*,int*,int*,int*) ;} ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ A_XGM_INT_STATUS ; 
 scalar_t__ A_XGM_RX_CTRL ; 
 scalar_t__ A_XGM_XAUI_ACT_CTRL ; 
 int DUPLEX_INVALID ; 
 int F_LINKFAULTCHANGE ; 
 int F_RXEN ; 
 int F_TXACTENABLE ; 
 int /*<<< orphan*/  MAC_DIRECTION_RX ; 
 int PAUSE_AUTONEG ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int SPEED_INVALID ; 
 struct port_info* adap2pinfo (struct adapter*,int) ; 
 int /*<<< orphan*/  stub1 (struct cphy*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  t3_gate_rx_traffic (struct cmac*,int*,int*,int*) ; 
 int /*<<< orphan*/  t3_mac_enable (struct cmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_mac_set_speed_duplex_fc (struct cmac*,int,int,int) ; 
 int /*<<< orphan*/  t3_open_rx_traffic (struct cmac*,int,int,int) ; 
 int /*<<< orphan*/  t3_os_link_changed (struct adapter*,int,int,int,int,int) ; 
 int t3_read_reg (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,scalar_t__,int) ; 
 int /*<<< orphan*/  t3_xgm_intr_enable (struct adapter*,int) ; 
 int /*<<< orphan*/  t3b_pcs_reset (struct cmac*) ; 
 scalar_t__ uses_xaui (struct adapter*) ; 

void t3_link_changed(struct adapter *adapter, int port_id)
{
	int link_ok, speed, duplex, fc;
	struct port_info *pi = adap2pinfo(adapter, port_id);
	struct cphy *phy = &pi->phy;
	struct cmac *mac = &pi->mac;
	struct link_config *lc = &pi->link_config;

	phy->ops->get_link_status(phy, &link_ok, &speed, &duplex, &fc);

	if (!lc->link_ok && link_ok) {
		u32 rx_cfg, rx_hash_high, rx_hash_low;
		u32 status;

		t3_xgm_intr_enable(adapter, port_id);
		t3_gate_rx_traffic(mac, &rx_cfg, &rx_hash_high, &rx_hash_low);
		t3_write_reg(adapter, A_XGM_RX_CTRL + mac->offset, 0);
		t3_mac_enable(mac, MAC_DIRECTION_RX);

		status = t3_read_reg(adapter, A_XGM_INT_STATUS + mac->offset);
		if (status & F_LINKFAULTCHANGE) {
			mac->stats.link_faults++;
			pi->link_fault = 1;
		}
		t3_open_rx_traffic(mac, rx_cfg, rx_hash_high, rx_hash_low);
	}

	if (lc->requested_fc & PAUSE_AUTONEG)
		fc &= lc->requested_fc;
	else
		fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);

	if (link_ok == lc->link_ok && speed == lc->speed &&
	    duplex == lc->duplex && fc == lc->fc)
		return;                            /* nothing changed */

	if (link_ok != lc->link_ok && adapter->params.rev > 0 &&
	    uses_xaui(adapter)) {
		if (link_ok)
			t3b_pcs_reset(mac);
		t3_write_reg(adapter, A_XGM_XAUI_ACT_CTRL + mac->offset,
			     link_ok ? F_TXACTENABLE | F_RXEN : 0);
	}
	lc->link_ok = link_ok;
	lc->speed = speed < 0 ? SPEED_INVALID : speed;
	lc->duplex = duplex < 0 ? DUPLEX_INVALID : duplex;

	if (link_ok && speed >= 0 && lc->autoneg == AUTONEG_ENABLE) {
		/* Set MAC speed, duplex, and flow control to match PHY. */
		t3_mac_set_speed_duplex_fc(mac, speed, duplex, fc);
		lc->fc = fc;
	}

	t3_os_link_changed(adapter, port_id, link_ok && !pi->link_fault,
			   speed, duplex, fc);
}