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
struct TYPE_4__ {scalar_t__ echo; int /*<<< orphan*/  func_bit_map; } ;
struct TYPE_6__ {TYPE_1__ vif_list_event; } ;
struct TYPE_5__ {TYPE_3__ data; } ;
union event_ring_elem {TYPE_2__ message; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_AFEX_LISTGET_ACK ; 
 int /*<<< orphan*/  DRV_MSG_CODE_AFEX_LISTSET_ACK ; 
 scalar_t__ VIF_LIST_RULE_GET ; 
 scalar_t__ VIF_LIST_RULE_SET ; 
 int /*<<< orphan*/  bnx2x_fw_command (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_after_afex_vif_lists(struct bnx2x *bp,
					      union event_ring_elem *elem)
{
	if (elem->message.data.vif_list_event.echo == VIF_LIST_RULE_GET) {
		DP(BNX2X_MSG_SP,
		   "afex: ramrod completed VIF LIST_GET, addrs 0x%x\n",
		   elem->message.data.vif_list_event.func_bit_map);
		bnx2x_fw_command(bp, DRV_MSG_CODE_AFEX_LISTGET_ACK,
			elem->message.data.vif_list_event.func_bit_map);
	} else if (elem->message.data.vif_list_event.echo ==
		   VIF_LIST_RULE_SET) {
		DP(BNX2X_MSG_SP, "afex: ramrod completed VIF LIST_SET\n");
		bnx2x_fw_command(bp, DRV_MSG_CODE_AFEX_LISTSET_ACK, 0);
	}
}