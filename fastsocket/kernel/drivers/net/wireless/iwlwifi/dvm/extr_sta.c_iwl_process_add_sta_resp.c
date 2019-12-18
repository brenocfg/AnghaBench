#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_6__ {int flags; } ;
struct iwl_rx_packet {TYPE_1__ hdr; scalar_t__ data; } ;
struct iwl_priv {int /*<<< orphan*/  sta_lock; TYPE_4__* stations; } ;
struct TYPE_10__ {size_t sta_id; int /*<<< orphan*/  addr; } ;
struct iwl_addsta_cmd {TYPE_5__ sta; } ;
struct iwl_add_sta_resp {int status; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {scalar_t__ mode; TYPE_2__ sta; } ;
struct TYPE_9__ {TYPE_3__ sta; } ;

/* Variables and functions */
#define  ADD_STA_MODIFY_NON_EXIST_STA 131 
#define  ADD_STA_NO_BLOCK_ACK_RESOURCE 130 
#define  ADD_STA_NO_ROOM_IN_TABLE 129 
#define  ADD_STA_SUCCESS_MSK 128 
 int EIO ; 
 int IWL_CMD_FAILED_MSK ; 
 int /*<<< orphan*/  IWL_DEBUG_ASSOC (struct iwl_priv*,char*,int) ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,size_t) ; 
 scalar_t__ STA_CONTROL_MODIFY_MSK ; 
 int iwl_sta_ucode_activate (struct iwl_priv*,size_t) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_process_add_sta_resp(struct iwl_priv *priv,
				    struct iwl_addsta_cmd *addsta,
				    struct iwl_rx_packet *pkt)
{
	struct iwl_add_sta_resp *add_sta_resp = (void *)pkt->data;
	u8 sta_id = addsta->sta.sta_id;
	int ret = -EIO;

	if (pkt->hdr.flags & IWL_CMD_FAILED_MSK) {
		IWL_ERR(priv, "Bad return from REPLY_ADD_STA (0x%08X)\n",
			pkt->hdr.flags);
		return ret;
	}

	IWL_DEBUG_INFO(priv, "Processing response for adding station %u\n",
		       sta_id);

	spin_lock_bh(&priv->sta_lock);

	switch (add_sta_resp->status) {
	case ADD_STA_SUCCESS_MSK:
		IWL_DEBUG_INFO(priv, "REPLY_ADD_STA PASSED\n");
		ret = iwl_sta_ucode_activate(priv, sta_id);
		break;
	case ADD_STA_NO_ROOM_IN_TABLE:
		IWL_ERR(priv, "Adding station %d failed, no room in table.\n",
			sta_id);
		break;
	case ADD_STA_NO_BLOCK_ACK_RESOURCE:
		IWL_ERR(priv, "Adding station %d failed, no block ack "
			"resource.\n", sta_id);
		break;
	case ADD_STA_MODIFY_NON_EXIST_STA:
		IWL_ERR(priv, "Attempting to modify non-existing station %d\n",
			sta_id);
		break;
	default:
		IWL_DEBUG_ASSOC(priv, "Received REPLY_ADD_STA:(0x%08X)\n",
				add_sta_resp->status);
		break;
	}

	IWL_DEBUG_INFO(priv, "%s station id %u addr %pM\n",
		       priv->stations[sta_id].sta.mode ==
		       STA_CONTROL_MODIFY_MSK ?  "Modified" : "Added",
		       sta_id, priv->stations[sta_id].sta.sta.addr);

	/*
	 * XXX: The MAC address in the command buffer is often changed from
	 * the original sent to the device. That is, the MAC address
	 * written to the command buffer often is not the same MAC address
	 * read from the command buffer when the command returns. This
	 * issue has not yet been resolved and this debugging is left to
	 * observe the problem.
	 */
	IWL_DEBUG_INFO(priv, "%s station according to cmd buffer %pM\n",
		       priv->stations[sta_id].sta.mode ==
		       STA_CONTROL_MODIFY_MSK ? "Modified" : "Added",
		       addsta->sta.addr);
	spin_unlock_bh(&priv->sta_lock);

	return ret;
}