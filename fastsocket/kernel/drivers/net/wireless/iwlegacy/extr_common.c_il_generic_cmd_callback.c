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
struct TYPE_3__ {int flags; } ;
struct il_rx_pkt {TYPE_1__ hdr; } ;
struct il_priv {int dummy; } ;
struct TYPE_4__ {int cmd; } ;
struct il_device_cmd {TYPE_2__ hdr; } ;

/* Variables and functions */
#define  C_SENSITIVITY 129 
#define  C_TX_LINK_QUALITY_CMD 128 
 int /*<<< orphan*/  D_HC (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  D_HC_DUMP (char*,int /*<<< orphan*/ ,int) ; 
 int IL_CMD_FAILED_MSK ; 
 int /*<<< orphan*/  IL_ERR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  il_get_cmd_string (int) ; 

__attribute__((used)) static void
il_generic_cmd_callback(struct il_priv *il, struct il_device_cmd *cmd,
			struct il_rx_pkt *pkt)
{
	if (pkt->hdr.flags & IL_CMD_FAILED_MSK) {
		IL_ERR("Bad return from %s (0x%08X)\n",
		       il_get_cmd_string(cmd->hdr.cmd), pkt->hdr.flags);
		return;
	}
#ifdef CONFIG_IWLEGACY_DEBUG
	switch (cmd->hdr.cmd) {
	case C_TX_LINK_QUALITY_CMD:
	case C_SENSITIVITY:
		D_HC_DUMP("back from %s (0x%08X)\n",
			  il_get_cmd_string(cmd->hdr.cmd), pkt->hdr.flags);
		break;
	default:
		D_HC("back from %s (0x%08X)\n", il_get_cmd_string(cmd->hdr.cmd),
		     pkt->hdr.flags);
	}
#endif
}