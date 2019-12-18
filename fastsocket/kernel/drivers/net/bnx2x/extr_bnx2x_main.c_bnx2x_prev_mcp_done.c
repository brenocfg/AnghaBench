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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_DONE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_SKIP_LINK_RESET ; 
 int EBUSY ; 
 int /*<<< orphan*/  bnx2x_fw_command (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_prev_mcp_done(struct bnx2x *bp)
{
	u32 rc = bnx2x_fw_command(bp, DRV_MSG_CODE_UNLOAD_DONE,
				  DRV_MSG_CODE_UNLOAD_SKIP_LINK_RESET);
	if (!rc) {
		BNX2X_ERR("MCP response failure, aborting\n");
		return -EBUSY;
	}

	return 0;
}