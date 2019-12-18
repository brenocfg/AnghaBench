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
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*) ; 
 int BNX2X_PREV_WAIT_NEEDED ; 
 int /*<<< orphan*/  FW_MSG_CODE_DRV_LOAD_FUNCTION ; 
 int bnx2x_do_flr (struct bnx2x*) ; 
 int bnx2x_nic_load_analyze_req (struct bnx2x*,int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2x_prev_is_path_marked (struct bnx2x*) ; 
 int bnx2x_prev_mcp_done (struct bnx2x*) ; 

__attribute__((used)) static int bnx2x_prev_unload_uncommon(struct bnx2x *bp)
{
	int rc;

	BNX2X_DEV_INFO("Uncommon unload Flow\n");

	/* Test if previous unload process was already finished for this path */
	if (bnx2x_prev_is_path_marked(bp))
		return bnx2x_prev_mcp_done(bp);

	BNX2X_DEV_INFO("Path is unmarked\n");

	/* If function has FLR capabilities, and existing FW version matches
	 * the one required, then FLR will be sufficient to clean any residue
	 * left by previous driver
	 */
	rc = bnx2x_nic_load_analyze_req(bp, FW_MSG_CODE_DRV_LOAD_FUNCTION);

	if (!rc) {
		/* fw version is good */
		BNX2X_DEV_INFO("FW version matches our own. Attempting FLR\n");
		rc = bnx2x_do_flr(bp);
	}

	if (!rc) {
		/* FLR was performed */
		BNX2X_DEV_INFO("FLR successful\n");
		return 0;
	}

	BNX2X_DEV_INFO("Could not FLR\n");

	/* Close the MCP request, return failure*/
	rc = bnx2x_prev_mcp_done(bp);
	if (!rc)
		rc = BNX2X_PREV_WAIT_NEEDED;

	return rc;
}