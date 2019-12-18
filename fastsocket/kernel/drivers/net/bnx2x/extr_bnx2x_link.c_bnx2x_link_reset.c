#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct link_vars {int eee_status; scalar_t__ phy_flags; scalar_t__ link_up; scalar_t__ link_status; } ;
struct link_params {int port; int num_phys; TYPE_1__* phy; int /*<<< orphan*/  chip_id; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  (* link_reset ) (TYPE_1__*,struct link_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E3 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int EXT_PHY1 ; 
 int FLAGS_REARM_LATCH_SIGNAL ; 
 scalar_t__ GRCBASE_MISC ; 
 scalar_t__ GRCBASE_XMAC0 ; 
 scalar_t__ GRCBASE_XMAC1 ; 
 size_t INT_PHY ; 
 int /*<<< orphan*/  LED_MODE_OFF ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_2_CLEAR ; 
 int MISC_REGISTERS_RESET_REG_2_RST_BMAC0 ; 
 int MISC_REGISTERS_RESET_REG_2_XMAC ; 
 int /*<<< orphan*/  MISC_REG_RESET_REG_2 ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int NIG_LATCH_BC_ENABLE_MI_INT ; 
 int NIG_MASK_MI_INT ; 
 int NIG_MASK_SERDES0_LINK_STATUS ; 
 int NIG_MASK_XGXS0_LINK10G ; 
 int NIG_MASK_XGXS0_LINK_STATUS ; 
 scalar_t__ NIG_REG_BMAC0_IN_EN ; 
 scalar_t__ NIG_REG_BMAC0_OUT_EN ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
 scalar_t__ NIG_REG_EGRESS_EMAC0_OUT_EN ; 
 scalar_t__ NIG_REG_EMAC0_IN_EN ; 
 scalar_t__ NIG_REG_LATCH_BC_0 ; 
 scalar_t__ NIG_REG_MASK_INTERRUPT_PORT0 ; 
 scalar_t__ NIG_REG_NIG_EMAC0_EN ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int SHMEM_EEE_ACTIVE_BIT ; 
 int SHMEM_EEE_LP_ADV_STATUS_MASK ; 
 int XMAC_CTRL_REG_SOFT_RESET ; 
 scalar_t__ XMAC_REG_CTRL ; 
 int /*<<< orphan*/  bnx2x_bits_dis (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  bnx2x_rearm_latch_signal (struct bnx2x*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_aer_mmd (struct link_params*,TYPE_1__*) ; 
 int /*<<< orphan*/  bnx2x_set_bmac_rx (struct bnx2x*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_led (struct link_params*,struct link_vars*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_mdio_emac_per_phy (struct bnx2x*,struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_set_umac_rxtx (struct link_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_xmac_rxtx (struct link_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_xumac_nig (struct link_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_update_mng (struct link_params*,scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_update_mng_eee (struct link_params*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct link_params*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,struct link_params*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int bnx2x_link_reset(struct link_params *params, struct link_vars *vars,
		     u8 reset_ext_phy)
{
	struct bnx2x *bp = params->bp;
	u8 phy_index, port = params->port, clear_latch_ind = 0;
	DP(NETIF_MSG_LINK, "Resetting the link of port %d\n", port);
	/* Disable attentions */
	vars->link_status = 0;
	bnx2x_update_mng(params, vars->link_status);
	vars->eee_status &= ~(SHMEM_EEE_LP_ADV_STATUS_MASK |
			      SHMEM_EEE_ACTIVE_BIT);
	bnx2x_update_mng_eee(params, vars->eee_status);
	bnx2x_bits_dis(bp, NIG_REG_MASK_INTERRUPT_PORT0 + port*4,
		       (NIG_MASK_XGXS0_LINK_STATUS |
			NIG_MASK_XGXS0_LINK10G |
			NIG_MASK_SERDES0_LINK_STATUS |
			NIG_MASK_MI_INT));

	/* Activate nig drain */
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + port*4, 1);

	/* Disable nig egress interface */
	if (!CHIP_IS_E3(bp)) {
		REG_WR(bp, NIG_REG_BMAC0_OUT_EN + port*4, 0);
		REG_WR(bp, NIG_REG_EGRESS_EMAC0_OUT_EN + port*4, 0);
	}

		if (!CHIP_IS_E3(bp)) {
			bnx2x_set_bmac_rx(bp, params->chip_id, port, 0);
		} else {
			bnx2x_set_xmac_rxtx(params, 0);
			bnx2x_set_umac_rxtx(params, 0);
		}
	/* Disable emac */
	if (!CHIP_IS_E3(bp))
		REG_WR(bp, NIG_REG_NIG_EMAC0_EN + port*4, 0);

	usleep_range(10000, 20000);
	/* The PHY reset is controlled by GPIO 1
	 * Hold it as vars low
	 */
	 /* Clear link led */
	bnx2x_set_mdio_emac_per_phy(bp, params);
	bnx2x_set_led(params, vars, LED_MODE_OFF, 0);

	if (reset_ext_phy) {
		for (phy_index = EXT_PHY1; phy_index < params->num_phys;
		      phy_index++) {
			if (params->phy[phy_index].link_reset) {
				bnx2x_set_aer_mmd(params,
						  &params->phy[phy_index]);
				params->phy[phy_index].link_reset(
					&params->phy[phy_index],
					params);
			}
			if (params->phy[phy_index].flags &
			    FLAGS_REARM_LATCH_SIGNAL)
				clear_latch_ind = 1;
		}
	}

	if (clear_latch_ind) {
		/* Clear latching indication */
		bnx2x_rearm_latch_signal(bp, port, 0);
		bnx2x_bits_dis(bp, NIG_REG_LATCH_BC_0 + port*4,
			       1 << NIG_LATCH_BC_ENABLE_MI_INT);
	}
	if (params->phy[INT_PHY].link_reset)
		params->phy[INT_PHY].link_reset(
			&params->phy[INT_PHY], params);

	/* Disable nig ingress interface */
	if (!CHIP_IS_E3(bp)) {
		/* Reset BigMac */
		REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
		       (MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port));
		REG_WR(bp, NIG_REG_BMAC0_IN_EN + port*4, 0);
		REG_WR(bp, NIG_REG_EMAC0_IN_EN + port*4, 0);
	} else {
		u32 xmac_base = (params->port) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;
		bnx2x_set_xumac_nig(params, 0, 0);
		if (REG_RD(bp, MISC_REG_RESET_REG_2) &
		    MISC_REGISTERS_RESET_REG_2_XMAC)
			REG_WR(bp, xmac_base + XMAC_REG_CTRL,
			       XMAC_CTRL_REG_SOFT_RESET);
	}
	vars->link_up = 0;
	vars->phy_flags = 0;
	return 0;
}