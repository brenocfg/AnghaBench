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
struct link_vars {scalar_t__ line_speed; int eee_status; int flow_ctrl; int /*<<< orphan*/  mac_type; } ;
struct link_params {int port; TYPE_1__* phy; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int flags; int supported; } ;

/* Variables and functions */
 int BNX2X_FLOW_CTRL_TX ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int FLAGS_TX_ERROR_CHECK ; 
 int GRCBASE_XMAC0 ; 
 int GRCBASE_XMAC1 ; 
 size_t INT_PHY ; 
 int /*<<< orphan*/  MAC_TYPE_XMAC ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int NIG_REG_EGRESS_EMAC0_PORT ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 int SHMEM_EEE_ADV_STATUS_MASK ; 
 scalar_t__ SPEED_20000 ; 
 int SUPPORTED_20000baseKR2_Full ; 
 int XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_LOCAL_FAULT_STATUS ; 
 int XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_REMOTE_FAULT_STATUS ; 
 int XMAC_CTRL_REG_LINE_LOCAL_LPBK ; 
 int XMAC_CTRL_REG_RX_EN ; 
 int XMAC_CTRL_REG_TX_EN ; 
 int XMAC_CTRL_REG_XLGMII_ALIGN_ENB ; 
 int XMAC_REG_CLEAR_RX_LSS_STATUS ; 
 int XMAC_REG_CTRL ; 
 int XMAC_REG_EEE_CTRL ; 
 int XMAC_REG_EEE_TIMERS_HI ; 
 int XMAC_REG_RX_LSS_CTRL ; 
 int XMAC_REG_RX_MAX_SIZE ; 
 int XMAC_REG_TX_CTRL ; 
 int XMAC_RX_LSS_CTRL_REG_LOCAL_FAULT_DISABLE ; 
 int XMAC_RX_LSS_CTRL_REG_REMOTE_FAULT_DISABLE ; 
 int /*<<< orphan*/  bnx2x_set_xumac_nig (struct link_params*,int,int) ; 
 int /*<<< orphan*/  bnx2x_update_pfc_xmac (struct link_params*,struct link_vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_xmac_init (struct link_params*,scalar_t__) ; 

__attribute__((used)) static int bnx2x_xmac_enable(struct link_params *params,
			     struct link_vars *vars, u8 lb)
{
	u32 val, xmac_base;
	struct bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "enabling XMAC\n");

	xmac_base = (params->port) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;

	bnx2x_xmac_init(params, vars->line_speed);

	/* This register determines on which events the MAC will assert
	 * error on the i/f to the NIG along w/ EOP.
	 */

	/* This register tells the NIG whether to send traffic to UMAC
	 * or XMAC
	 */
	REG_WR(bp, NIG_REG_EGRESS_EMAC0_PORT + params->port*4, 0);

	/* When XMAC is in XLGMII mode, disable sending idles for fault
	 * detection.
	 */
	if (!(params->phy[INT_PHY].flags & FLAGS_TX_ERROR_CHECK)) {
		REG_WR(bp, xmac_base + XMAC_REG_RX_LSS_CTRL,
		       (XMAC_RX_LSS_CTRL_REG_LOCAL_FAULT_DISABLE |
			XMAC_RX_LSS_CTRL_REG_REMOTE_FAULT_DISABLE));
		REG_WR(bp, xmac_base + XMAC_REG_CLEAR_RX_LSS_STATUS, 0);
		REG_WR(bp, xmac_base + XMAC_REG_CLEAR_RX_LSS_STATUS,
		       XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_LOCAL_FAULT_STATUS |
		       XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_REMOTE_FAULT_STATUS);
	}
	/* Set Max packet size */
	REG_WR(bp, xmac_base + XMAC_REG_RX_MAX_SIZE, 0x2710);

	/* CRC append for Tx packets */
	REG_WR(bp, xmac_base + XMAC_REG_TX_CTRL, 0xC800);

	/* update PFC */
	bnx2x_update_pfc_xmac(params, vars, 0);

	if (vars->eee_status & SHMEM_EEE_ADV_STATUS_MASK) {
		DP(NETIF_MSG_LINK, "Setting XMAC for EEE\n");
		REG_WR(bp, xmac_base + XMAC_REG_EEE_TIMERS_HI, 0x1380008);
		REG_WR(bp, xmac_base + XMAC_REG_EEE_CTRL, 0x1);
	} else {
		REG_WR(bp, xmac_base + XMAC_REG_EEE_CTRL, 0x0);
	}

	/* Enable TX and RX */
	val = XMAC_CTRL_REG_TX_EN | XMAC_CTRL_REG_RX_EN;

	/* Set MAC in XLGMII mode for dual-mode */
	if ((vars->line_speed == SPEED_20000) &&
	    (params->phy[INT_PHY].supported &
	     SUPPORTED_20000baseKR2_Full))
		val |= XMAC_CTRL_REG_XLGMII_ALIGN_ENB;

	/* Check loopback mode */
	if (lb)
		val |= XMAC_CTRL_REG_LINE_LOCAL_LPBK;
	REG_WR(bp, xmac_base + XMAC_REG_CTRL, val);
	bnx2x_set_xumac_nig(params,
			    ((vars->flow_ctrl & BNX2X_FLOW_CTRL_TX) != 0), 1);

	vars->mac_type = MAC_TYPE_XMAC;

	return 0;
}