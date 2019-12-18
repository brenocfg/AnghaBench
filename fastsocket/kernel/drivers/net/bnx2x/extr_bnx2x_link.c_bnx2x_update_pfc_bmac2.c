#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct link_vars {int flow_ctrl; } ;
struct link_params {int feature_config_flags; scalar_t__ port; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BIGMAC2_REGISTER_BMAC_CONTROL ; 
 int BIGMAC2_REGISTER_PFC_CONTROL ; 
 int BIGMAC2_REGISTER_RX_CONTROL ; 
 int BIGMAC2_REGISTER_TX_CONTROL ; 
 int BIGMAC2_REGISTER_TX_PAUSE_CONTROL ; 
 int BNX2X_FLOW_CTRL_RX ; 
 int BNX2X_FLOW_CTRL_TX ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int FEATURE_CONFIG_PFC_ENABLED ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int NIG_REG_INGRESS_BMAC0_MEM ; 
 int NIG_REG_INGRESS_BMAC1_MEM ; 
 int /*<<< orphan*/  REG_WR_DMAE (struct bnx2x*,int,int*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bnx2x_update_pfc_bmac2(struct link_params *params,
				   struct link_vars *vars,
				   u8 is_lb)
{
	/* Set rx control: Strip CRC and enable BigMAC to relay
	 * control packets to the system as well
	 */
	u32 wb_data[2];
	struct bnx2x *bp = params->bp;
	u32 bmac_addr = params->port ? NIG_REG_INGRESS_BMAC1_MEM :
		NIG_REG_INGRESS_BMAC0_MEM;
	u32 val = 0x14;

	if ((!(params->feature_config_flags &
	      FEATURE_CONFIG_PFC_ENABLED)) &&
		(vars->flow_ctrl & BNX2X_FLOW_CTRL_RX))
		/* Enable BigMAC to react on received Pause packets */
		val |= (1<<5);
	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_RX_CONTROL, wb_data, 2);
	udelay(30);

	/* Tx control */
	val = 0xc0;
	if (!(params->feature_config_flags &
				FEATURE_CONFIG_PFC_ENABLED) &&
	    (vars->flow_ctrl & BNX2X_FLOW_CTRL_TX))
		val |= 0x800000;
	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_TX_CONTROL, wb_data, 2);

	if (params->feature_config_flags & FEATURE_CONFIG_PFC_ENABLED) {
		DP(NETIF_MSG_LINK, "PFC is enabled\n");
		/* Enable PFC RX & TX & STATS and set 8 COS  */
		wb_data[0] = 0x0;
		wb_data[0] |= (1<<0);  /* RX */
		wb_data[0] |= (1<<1);  /* TX */
		wb_data[0] |= (1<<2);  /* Force initial Xon */
		wb_data[0] |= (1<<3);  /* 8 cos */
		wb_data[0] |= (1<<5);  /* STATS */
		wb_data[1] = 0;
		REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_PFC_CONTROL,
			    wb_data, 2);
		/* Clear the force Xon */
		wb_data[0] &= ~(1<<2);
	} else {
		DP(NETIF_MSG_LINK, "PFC is disabled\n");
		/* Disable PFC RX & TX & STATS and set 8 COS */
		wb_data[0] = 0x8;
		wb_data[1] = 0;
	}

	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_PFC_CONTROL, wb_data, 2);

	/* Set Time (based unit is 512 bit time) between automatic
	 * re-sending of PP packets amd enable automatic re-send of
	 * Per-Priroity Packet as long as pp_gen is asserted and
	 * pp_disable is low.
	 */
	val = 0x8000;
	if (params->feature_config_flags & FEATURE_CONFIG_PFC_ENABLED)
		val |= (1<<16); /* enable automatic re-send */

	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_TX_PAUSE_CONTROL,
		    wb_data, 2);

	/* mac control */
	val = 0x3; /* Enable RX and TX */
	if (is_lb) {
		val |= 0x4; /* Local loopback */
		DP(NETIF_MSG_LINK, "enable bmac loopback\n");
	}
	/* When PFC enabled, Pass pause frames towards the NIG. */
	if (params->feature_config_flags & FEATURE_CONFIG_PFC_ENABLED)
		val |= ((1<<6)|(1<<5));

	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_BMAC_CONTROL, wb_data, 2);
}