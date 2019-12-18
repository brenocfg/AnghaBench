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
typedef  int u8 ;
typedef  int u32 ;
struct link_vars {int phy_flags; int link_up; int link_status; int /*<<< orphan*/  periodic_flags; } ;
struct link_params {int port; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int LED_MODE_OFF ; 
 int LED_MODE_OPER ; 
 int LINK_STATUS_LINK_UP ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
 int /*<<< orphan*/  PERIODIC_FLAGS_LINK_EVENT ; 
#define  PHY_HALF_OPEN_CONN_FLAG 129 
#define  PHY_SFP_TX_FAULT_FLAG 128 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  bnx2x_notify_link_changed (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_set_led (struct link_params*,struct link_vars*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_sync_link (struct link_params*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_update_mng (struct link_params*,int) ; 

__attribute__((used)) static u8 bnx2x_analyze_link_error(struct link_params *params,
				    struct link_vars *vars, u32 status,
				    u32 phy_flag, u32 link_flag, u8 notify)
{
	struct bnx2x *bp = params->bp;
	/* Compare new value with previous value */
	u8 led_mode;
	u32 old_status = (vars->phy_flags & phy_flag) ? 1 : 0;

	if ((status ^ old_status) == 0)
		return 0;

	/* If values differ */
	switch (phy_flag) {
	case PHY_HALF_OPEN_CONN_FLAG:
		DP(NETIF_MSG_LINK, "Analyze Remote Fault\n");
		break;
	case PHY_SFP_TX_FAULT_FLAG:
		DP(NETIF_MSG_LINK, "Analyze TX Fault\n");
		break;
	default:
		DP(NETIF_MSG_LINK, "Analyze UNKNOWN\n");
	}
	DP(NETIF_MSG_LINK, "Link changed:[%x %x]->%x\n", vars->link_up,
	   old_status, status);

	/* a. Update shmem->link_status accordingly
	 * b. Update link_vars->link_up
	 */
	if (status) {
		vars->link_status &= ~LINK_STATUS_LINK_UP;
		vars->link_status |= link_flag;
		vars->link_up = 0;
		vars->phy_flags |= phy_flag;

		/* activate nig drain */
		REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 1);
		/* Set LED mode to off since the PHY doesn't know about these
		 * errors
		 */
		led_mode = LED_MODE_OFF;
	} else {
		vars->link_status |= LINK_STATUS_LINK_UP;
		vars->link_status &= ~link_flag;
		vars->link_up = 1;
		vars->phy_flags &= ~phy_flag;
		led_mode = LED_MODE_OPER;

		/* Clear nig drain */
		REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);
	}
	bnx2x_sync_link(params, vars);
	/* Update the LED according to the link state */
	bnx2x_set_led(params, vars, led_mode, SPEED_10000);

	/* Update link status in the shared memory */
	bnx2x_update_mng(params, vars->link_status);

	/* C. Trigger General Attention */
	vars->periodic_flags |= PERIODIC_FLAGS_LINK_EVENT;
	if (notify)
		bnx2x_notify_link_changed(bp);

	return 1;
}