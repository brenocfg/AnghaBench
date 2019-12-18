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
struct link_vars {int link_status; int phy_flags; int flow_ctrl; int eee_status; int /*<<< orphan*/  line_speed; scalar_t__ link_up; } ;
struct link_params {int port; TYPE_1__* phy; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int BNX2X_FLOW_CTRL_RX ; 
 int BNX2X_FLOW_CTRL_TX ; 
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E2 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESRCH ; 
 int FLAGS_TX_ERROR_CHECK ; 
 int INT_PHY ; 
 int /*<<< orphan*/  LED_MODE_OPER ; 
 int LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int LINK_STATUS_LINK_UP ; 
 int LINK_STATUS_PHYSICAL_LINK_FLAG ; 
 int LINK_STATUS_RX_FLOW_CONTROL_ENABLED ; 
 int LINK_STATUS_TX_FLOW_CONTROL_ENABLED ; 
 int MAX_PHYS ; 
 scalar_t__ MISC_REG_CPMU_LP_DR_ENABLE ; 
 scalar_t__ MISC_REG_CPMU_LP_FW_ENABLE_P0 ; 
 scalar_t__ MISC_REG_CPMU_LP_MASK_ENT_P0 ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
 int PHY_HALF_OPEN_CONN_FLAG ; 
 int PHY_PHYSICAL_LINK_FLAG ; 
 int PHY_SGMII_FLAG ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int SHMEM_EEE_ACTIVE_BIT ; 
 int SHMEM_EEE_LPI_REQUESTED_BIT ; 
 scalar_t__ SINGLE_MEDIA_DIRECT (struct link_params*) ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 scalar_t__ USES_WARPCORE (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_bmac_enable (struct link_params*,struct link_vars*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_check_half_open_conn (struct link_params*,struct link_vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_emac_enable (struct link_params*,struct link_vars*,int /*<<< orphan*/ ) ; 
 int bnx2x_emac_program (struct link_params*,struct link_vars*) ; 
 int bnx2x_pbf_update (struct link_params*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_gmii_tx_driver (struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_set_led (struct link_params*,struct link_vars*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_umac_enable (struct link_params*,struct link_vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_update_mng (struct link_params*,int) ; 
 int /*<<< orphan*/  bnx2x_update_mng_eee (struct link_params*,int) ; 
 int /*<<< orphan*/  bnx2x_xmac_enable (struct link_params*,struct link_vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int bnx2x_update_link_up(struct link_params *params,
				struct link_vars *vars,
				u8 link_10g)
{
	struct bnx2x *bp = params->bp;
	u8 phy_idx, port = params->port;
	int rc = 0;

	vars->link_status |= (LINK_STATUS_LINK_UP |
			      LINK_STATUS_PHYSICAL_LINK_FLAG);
	vars->phy_flags |= PHY_PHYSICAL_LINK_FLAG;

	if (vars->flow_ctrl & BNX2X_FLOW_CTRL_TX)
		vars->link_status |=
			LINK_STATUS_TX_FLOW_CONTROL_ENABLED;

	if (vars->flow_ctrl & BNX2X_FLOW_CTRL_RX)
		vars->link_status |=
			LINK_STATUS_RX_FLOW_CONTROL_ENABLED;
	if (USES_WARPCORE(bp)) {
		if (link_10g) {
			if (bnx2x_xmac_enable(params, vars, 0) ==
			    -ESRCH) {
				DP(NETIF_MSG_LINK, "Found errors on XMAC\n");
				vars->link_up = 0;
				vars->phy_flags |= PHY_HALF_OPEN_CONN_FLAG;
				vars->link_status &= ~LINK_STATUS_LINK_UP;
			}
		} else
			bnx2x_umac_enable(params, vars, 0);
		bnx2x_set_led(params, vars,
			      LED_MODE_OPER, vars->line_speed);

		if ((vars->eee_status & SHMEM_EEE_ACTIVE_BIT) &&
		    (vars->eee_status & SHMEM_EEE_LPI_REQUESTED_BIT)) {
			DP(NETIF_MSG_LINK, "Enabling LPI assertion\n");
			REG_WR(bp, MISC_REG_CPMU_LP_FW_ENABLE_P0 +
			       (params->port << 2), 1);
			REG_WR(bp, MISC_REG_CPMU_LP_DR_ENABLE, 1);
			REG_WR(bp, MISC_REG_CPMU_LP_MASK_ENT_P0 +
			       (params->port << 2), 0xfc20);
		}
	}
	if ((CHIP_IS_E1x(bp) ||
	     CHIP_IS_E2(bp))) {
		if (link_10g) {
			if (bnx2x_bmac_enable(params, vars, 0, 1) ==
			    -ESRCH) {
				DP(NETIF_MSG_LINK, "Found errors on BMAC\n");
				vars->link_up = 0;
				vars->phy_flags |= PHY_HALF_OPEN_CONN_FLAG;
				vars->link_status &= ~LINK_STATUS_LINK_UP;
			}

			bnx2x_set_led(params, vars,
				      LED_MODE_OPER, SPEED_10000);
		} else {
			rc = bnx2x_emac_program(params, vars);
			bnx2x_emac_enable(params, vars, 0);

			/* AN complete? */
			if ((vars->link_status &
			     LINK_STATUS_AUTO_NEGOTIATE_COMPLETE)
			    && (!(vars->phy_flags & PHY_SGMII_FLAG)) &&
			    SINGLE_MEDIA_DIRECT(params))
				bnx2x_set_gmii_tx_driver(params);
		}
	}

	/* PBF - link up */
	if (CHIP_IS_E1x(bp))
		rc |= bnx2x_pbf_update(params, vars->flow_ctrl,
				       vars->line_speed);

	/* Disable drain */
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + port*4, 0);

	/* Update shared memory */
	bnx2x_update_mng(params, vars->link_status);
	bnx2x_update_mng_eee(params, vars->eee_status);
	/* Check remote fault */
	for (phy_idx = INT_PHY; phy_idx < MAX_PHYS; phy_idx++) {
		if (params->phy[phy_idx].flags & FLAGS_TX_ERROR_CHECK) {
			bnx2x_check_half_open_conn(params, vars, 0);
			break;
		}
	}
	msleep(20);
	return rc;
}