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
typedef  int u16 ;
struct link_vars {int dummy; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  PHY84833_CMD_SET_EEE_MODE ; 
 int /*<<< orphan*/  SHMEM_EEE_10G_ADV ; 
 int bnx2x_84833_cmd_hdlr (struct bnx2x_phy*,struct link_params*,int /*<<< orphan*/ ,int*,int) ; 
 int bnx2x_eee_advertise (struct bnx2x_phy*,struct link_params*,struct link_vars*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_8483x_enable_eee(struct bnx2x_phy *phy,
				   struct link_params *params,
				   struct link_vars *vars)
{
	int rc;
	struct bnx2x *bp = params->bp;
	u16 cmd_args = 1;

	rc = bnx2x_84833_cmd_hdlr(phy, params,
		PHY84833_CMD_SET_EEE_MODE, &cmd_args, 1);
	if (rc) {
		DP(NETIF_MSG_LINK, "EEE enable failed.\n");
		return rc;
	}

	return bnx2x_eee_advertise(phy, params, vars, SHMEM_EEE_10G_ADV);
}