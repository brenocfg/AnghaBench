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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BP_PATH (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int FW_MSG_CODE_DRV_LOAD_COMMON ; 
 int FW_MSG_CODE_DRV_LOAD_FUNCTION ; 
 int FW_MSG_CODE_DRV_LOAD_PORT ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int** load_count ; 

__attribute__((used)) static int bnx2x_nic_load_no_mcp(struct bnx2x *bp, int port)
{
	int path = BP_PATH(bp);

	DP(NETIF_MSG_IFUP, "NO MCP - load counts[%d]      %d, %d, %d\n",
	   path, load_count[path][0], load_count[path][1],
	   load_count[path][2]);
	load_count[path][0]++;
	load_count[path][1 + port]++;
	DP(NETIF_MSG_IFUP, "NO MCP - new load counts[%d]  %d, %d, %d\n",
	   path, load_count[path][0], load_count[path][1],
	   load_count[path][2]);
	if (load_count[path][0] == 1)
		return FW_MSG_CODE_DRV_LOAD_COMMON;
	else if (load_count[path][1 + port] == 1)
		return FW_MSG_CODE_DRV_LOAD_PORT;
	else
		return FW_MSG_CODE_DRV_LOAD_FUNCTION;
}