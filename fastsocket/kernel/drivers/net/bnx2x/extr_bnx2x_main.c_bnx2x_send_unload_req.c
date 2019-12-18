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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct bnx2x {int flags; scalar_t__ pm_cap; int /*<<< orphan*/  pdev; TYPE_1__* dev; scalar_t__ wol; } ;
struct TYPE_2__ {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_NOMCP (struct bnx2x*) ; 
 int BP_PATH (struct bnx2x*) ; 
 int BP_PORT (struct bnx2x*) ; 
 int BP_VN (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS ; 
 int DRV_MSG_CODE_UNLOAD_REQ_WOL_EN ; 
 int DRV_MSG_CODE_UNLOAD_REQ_WOL_MCP ; 
 int EMAC_REG_EMAC_MAC_MATCH ; 
 int /*<<< orphan*/  EMAC_WR (struct bnx2x*,int,int) ; 
 int FW_MSG_CODE_DRV_UNLOAD_COMMON ; 
 int FW_MSG_CODE_DRV_UNLOAD_FUNCTION ; 
 int FW_MSG_CODE_DRV_UNLOAD_PORT ; 
 int GRCBASE_EMAC0 ; 
 int GRCBASE_EMAC1 ; 
 int /*<<< orphan*/  NETIF_MSG_IFDOWN ; 
 int NO_WOL_FLAG ; 
 scalar_t__ PCI_PM_CTRL ; 
 int PCI_PM_CTRL_PME_ENABLE ; 
 int PCI_PM_CTRL_PME_STATUS ; 
 int UNLOAD_NORMAL ; 
 int bnx2x_fw_command (struct bnx2x*,int,int /*<<< orphan*/ ) ; 
 scalar_t__** load_count ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,scalar_t__,int) ; 

u32 bnx2x_send_unload_req(struct bnx2x *bp, int unload_mode)
{
	u32 reset_code = 0;
	int port = BP_PORT(bp);

	/* Select the UNLOAD request mode */
	if (unload_mode == UNLOAD_NORMAL)
		reset_code = DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS;

	else if (bp->flags & NO_WOL_FLAG)
		reset_code = DRV_MSG_CODE_UNLOAD_REQ_WOL_MCP;

	else if (bp->wol) {
		u32 emac_base = port ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
		u8 *mac_addr = bp->dev->dev_addr;
		u32 val;
		u16 pmc;

		/* The mac address is written to entries 1-4 to
		 * preserve entry 0 which is used by the PMF
		 */
		u8 entry = (BP_VN(bp) + 1)*8;

		val = (mac_addr[0] << 8) | mac_addr[1];
		EMAC_WR(bp, EMAC_REG_EMAC_MAC_MATCH + entry, val);

		val = (mac_addr[2] << 24) | (mac_addr[3] << 16) |
		      (mac_addr[4] << 8) | mac_addr[5];
		EMAC_WR(bp, EMAC_REG_EMAC_MAC_MATCH + entry + 4, val);

		/* Enable the PME and clear the status */
		pci_read_config_word(bp->pdev, bp->pm_cap + PCI_PM_CTRL, &pmc);
		pmc |= PCI_PM_CTRL_PME_ENABLE | PCI_PM_CTRL_PME_STATUS;
		pci_write_config_word(bp->pdev, bp->pm_cap + PCI_PM_CTRL, pmc);

		reset_code = DRV_MSG_CODE_UNLOAD_REQ_WOL_EN;

	} else
		reset_code = DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS;

	/* Send the request to the MCP */
	if (!BP_NOMCP(bp))
		reset_code = bnx2x_fw_command(bp, reset_code, 0);
	else {
		int path = BP_PATH(bp);

		DP(NETIF_MSG_IFDOWN, "NO MCP - load counts[%d]      %d, %d, %d\n",
		   path, load_count[path][0], load_count[path][1],
		   load_count[path][2]);
		load_count[path][0]--;
		load_count[path][1 + port]--;
		DP(NETIF_MSG_IFDOWN, "NO MCP - new load counts[%d]  %d, %d, %d\n",
		   path, load_count[path][0], load_count[path][1],
		   load_count[path][2]);
		if (load_count[path][0] == 0)
			reset_code = FW_MSG_CODE_DRV_UNLOAD_COMMON;
		else if (load_count[path][1 + port] == 0)
			reset_code = FW_MSG_CODE_DRV_UNLOAD_PORT;
		else
			reset_code = FW_MSG_CODE_DRV_UNLOAD_FUNCTION;
	}

	return reset_code;
}