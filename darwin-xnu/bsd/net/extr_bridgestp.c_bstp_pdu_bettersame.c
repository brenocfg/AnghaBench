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
struct TYPE_2__ {int /*<<< orphan*/  cu_pv; } ;
struct bstp_port {int bp_infois; int /*<<< orphan*/  bp_desg_pv; int /*<<< orphan*/  bp_port_pv; TYPE_1__ bp_msg_cu; } ;

/* Variables and functions */
 int BSTP_INFO_MINE ; 
 int BSTP_INFO_RECEIVED ; 
 scalar_t__ INFO_SAME ; 
 scalar_t__ bstp_info_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bstp_pdu_bettersame(struct bstp_port *bp, int newinfo)
{
	if (newinfo == BSTP_INFO_RECEIVED &&
	    bp->bp_infois == BSTP_INFO_RECEIVED &&
	    bstp_info_cmp(&bp->bp_port_pv, &bp->bp_msg_cu.cu_pv) >= INFO_SAME)
		return (1);

	if (newinfo == BSTP_INFO_MINE &&
	    bp->bp_infois == BSTP_INFO_MINE &&
	    bstp_info_cmp(&bp->bp_port_pv, &bp->bp_desg_pv) >= INFO_SAME)
		return (1);

	return (0);
}