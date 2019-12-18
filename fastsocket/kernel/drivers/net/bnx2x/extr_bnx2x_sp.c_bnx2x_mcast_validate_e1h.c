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
struct bnx2x_mcast_ramrod_params {int mcast_list_len; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_mcast_cmd { ____Placeholder_bnx2x_mcast_cmd } bnx2x_mcast_cmd ;

/* Variables and functions */
 int BNX2X_MCAST_CMD_DEL ; 
 int BNX2X_MCAST_CMD_RESTORE ; 

__attribute__((used)) static int bnx2x_mcast_validate_e1h(struct bnx2x *bp,
				    struct bnx2x_mcast_ramrod_params *p,
				    enum bnx2x_mcast_cmd cmd)
{
	/* Mark, that there is a work to do */
	if ((cmd == BNX2X_MCAST_CMD_DEL) || (cmd == BNX2X_MCAST_CMD_RESTORE))
		p->mcast_list_len = 1;

	return 0;
}