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
typedef  int u32 ;
struct link_vars {int /*<<< orphan*/  link_status; int /*<<< orphan*/  flow_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FLOW_CTRL_BOTH ; 
 int /*<<< orphan*/  BNX2X_FLOW_CTRL_RX ; 
 int /*<<< orphan*/  BNX2X_FLOW_CTRL_TX ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE ; 

__attribute__((used)) static void bnx2x_pause_resolve(struct link_vars *vars, u32 pause_result)
{						/*  LD	    LP	 */
	switch (pause_result) {			/* ASYM P ASYM P */
	case 0xb:				/*   1  0   1  1 */
		vars->flow_ctrl = BNX2X_FLOW_CTRL_TX;
		break;

	case 0xe:				/*   1  1   1  0 */
		vars->flow_ctrl = BNX2X_FLOW_CTRL_RX;
		break;

	case 0x5:				/*   0  1   0  1 */
	case 0x7:				/*   0  1   1  1 */
	case 0xd:				/*   1  1   0  1 */
	case 0xf:				/*   1  1   1  1 */
		vars->flow_ctrl = BNX2X_FLOW_CTRL_BOTH;
		break;

	default:
		break;
	}
	if (pause_result & (1<<0))
		vars->link_status |= LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE;
	if (pause_result & (1<<1))
		vars->link_status |= LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE;

}