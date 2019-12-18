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
struct TYPE_2__ {int flow_ctrl; scalar_t__ link_up; } ;
struct bnx2x {TYPE_1__ link_vars; scalar_t__ dropless_fc; } ;

/* Variables and functions */
 scalar_t__ BAR_USTRORM_INTMEM ; 
 int BNX2X_FLOW_CTRL_TX ; 
 int /*<<< orphan*/  BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int,char*,char*) ; 
 int NETIF_MSG_IFUP ; 
 int NETIF_MSG_LINK ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 scalar_t__ USTORM_ETH_PAUSE_ENABLED_OFFSET (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_init_dropless_fc(struct bnx2x *bp)
{
	u32 pause_enabled = 0;

	if (!CHIP_IS_E1(bp) && bp->dropless_fc && bp->link_vars.link_up) {
		if (bp->link_vars.flow_ctrl & BNX2X_FLOW_CTRL_TX)
			pause_enabled = 1;

		REG_WR(bp, BAR_USTRORM_INTMEM +
			   USTORM_ETH_PAUSE_ENABLED_OFFSET(BP_PORT(bp)),
		       pause_enabled);
	}

	DP(NETIF_MSG_IFUP | NETIF_MSG_LINK, "dropless_fc is %s\n",
	   pause_enabled ? "enabled" : "disabled");
}