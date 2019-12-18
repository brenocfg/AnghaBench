#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  req_fc_auto_adv; } ;
struct bnx2x {TYPE_2__ link_params; TYPE_1__* dev; } ;
struct TYPE_3__ {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FLOW_CTRL_BOTH ; 
 int /*<<< orphan*/  BNX2X_FLOW_CTRL_TX ; 
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 

__attribute__((used)) static void bnx2x_set_requested_fc(struct bnx2x *bp)
{
	/* Initialize link parameters structure variables
	 * It is recommended to turn off RX FC for jumbo frames
	 *  for better performance
	 */
	if (CHIP_IS_E1x(bp) && (bp->dev->mtu > 5000))
		bp->link_params.req_fc_auto_adv = BNX2X_FLOW_CTRL_TX;
	else
		bp->link_params.req_fc_auto_adv = BNX2X_FLOW_CTRL_BOTH;
}