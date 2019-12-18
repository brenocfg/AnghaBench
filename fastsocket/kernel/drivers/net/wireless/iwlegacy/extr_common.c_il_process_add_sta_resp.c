#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_9__ {int status; } ;
struct TYPE_10__ {TYPE_2__ add_sta; } ;
struct TYPE_8__ {int flags; } ;
struct il_rx_pkt {TYPE_3__ u; TYPE_1__ hdr; } ;
struct il_priv {int /*<<< orphan*/  sta_lock; TYPE_6__* stations; } ;
struct TYPE_14__ {size_t sta_id; int /*<<< orphan*/  addr; } ;
struct il_addsta_cmd {TYPE_7__ sta; } ;
struct TYPE_11__ {int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {scalar_t__ mode; TYPE_4__ sta; } ;
struct TYPE_13__ {TYPE_5__ sta; } ;

/* Variables and functions */
#define  ADD_STA_MODIFY_NON_EXIST_STA 131 
#define  ADD_STA_NO_BLOCK_ACK_RESOURCE 130 
#define  ADD_STA_NO_ROOM_IN_TBL 129 
#define  ADD_STA_SUCCESS_MSK 128 
 int /*<<< orphan*/  D_ASSOC (char*,int) ; 
 int /*<<< orphan*/  D_INFO (char*,...) ; 
 int EIO ; 
 int IL_CMD_FAILED_MSK ; 
 int /*<<< orphan*/  IL_ERR (char*,size_t) ; 
 scalar_t__ STA_CONTROL_MODIFY_MSK ; 
 int /*<<< orphan*/  il_sta_ucode_activate (struct il_priv*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
il_process_add_sta_resp(struct il_priv *il, struct il_addsta_cmd *addsta,
			struct il_rx_pkt *pkt, bool sync)
{
	u8 sta_id = addsta->sta.sta_id;
	unsigned long flags;
	int ret = -EIO;

	if (pkt->hdr.flags & IL_CMD_FAILED_MSK) {
		IL_ERR("Bad return from C_ADD_STA (0x%08X)\n", pkt->hdr.flags);
		return ret;
	}

	D_INFO("Processing response for adding station %u\n", sta_id);

	spin_lock_irqsave(&il->sta_lock, flags);

	switch (pkt->u.add_sta.status) {
	case ADD_STA_SUCCESS_MSK:
		D_INFO("C_ADD_STA PASSED\n");
		il_sta_ucode_activate(il, sta_id);
		ret = 0;
		break;
	case ADD_STA_NO_ROOM_IN_TBL:
		IL_ERR("Adding station %d failed, no room in table.\n", sta_id);
		break;
	case ADD_STA_NO_BLOCK_ACK_RESOURCE:
		IL_ERR("Adding station %d failed, no block ack resource.\n",
		       sta_id);
		break;
	case ADD_STA_MODIFY_NON_EXIST_STA:
		IL_ERR("Attempting to modify non-existing station %d\n",
		       sta_id);
		break;
	default:
		D_ASSOC("Received C_ADD_STA:(0x%08X)\n", pkt->u.add_sta.status);
		break;
	}

	D_INFO("%s station id %u addr %pM\n",
	       il->stations[sta_id].sta.mode ==
	       STA_CONTROL_MODIFY_MSK ? "Modified" : "Added", sta_id,
	       il->stations[sta_id].sta.sta.addr);

	/*
	 * XXX: The MAC address in the command buffer is often changed from
	 * the original sent to the device. That is, the MAC address
	 * written to the command buffer often is not the same MAC address
	 * read from the command buffer when the command returns. This
	 * issue has not yet been resolved and this debugging is left to
	 * observe the problem.
	 */
	D_INFO("%s station according to cmd buffer %pM\n",
	       il->stations[sta_id].sta.mode ==
	       STA_CONTROL_MODIFY_MSK ? "Modified" : "Added", addsta->sta.addr);
	spin_unlock_irqrestore(&il->sta_lock, flags);

	return ret;
}