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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ bcast_hlid; } ;
struct wl12xx_vif {TYPE_1__ ap; } ;
struct wl1271_cmd_set_keys {scalar_t__ key; int /*<<< orphan*/ * ac_seq_num32; void** ac_seq_num16; scalar_t__ key_id; scalar_t__ key_type; scalar_t__ key_size; void* key_action; scalar_t__ hlid; scalar_t__ lid_key_type; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 scalar_t__ BROADCAST_LID_TYPE ; 
 int /*<<< orphan*/  CMD_SET_KEYS ; 
 int /*<<< orphan*/  DEBUG_CRYPT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ KEY_TKIP ; 
 scalar_t__ KEY_WEP ; 
 scalar_t__ UNICAST_LID_TYPE ; 
 scalar_t__ WEP_DEFAULT_LID_TYPE ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1271_cmd_set_keys*) ; 
 struct wl1271_cmd_set_keys* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__ const*,scalar_t__) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_cmd_set_keys*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  wl1271_dump (int /*<<< orphan*/ ,char*,struct wl1271_cmd_set_keys*,int) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 

int wl1271_cmd_set_ap_key(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			  u16 action, u8 id, u8 key_type,
			  u8 key_size, const u8 *key, u8 hlid, u32 tx_seq_32,
			  u16 tx_seq_16)
{
	struct wl1271_cmd_set_keys *cmd;
	int ret = 0;
	u8 lid_type;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	if (hlid == wlvif->ap.bcast_hlid) {
		if (key_type == KEY_WEP)
			lid_type = WEP_DEFAULT_LID_TYPE;
		else
			lid_type = BROADCAST_LID_TYPE;
	} else {
		lid_type = UNICAST_LID_TYPE;
	}

	wl1271_debug(DEBUG_CRYPT, "ap key action: %d id: %d lid: %d type: %d"
		     " hlid: %d", (int)action, (int)id, (int)lid_type,
		     (int)key_type, (int)hlid);

	cmd->lid_key_type = lid_type;
	cmd->hlid = hlid;
	cmd->key_action = cpu_to_le16(action);
	cmd->key_size = key_size;
	cmd->key_type = key_type;
	cmd->key_id = id;
	cmd->ac_seq_num16[0] = cpu_to_le16(tx_seq_16);
	cmd->ac_seq_num32[0] = cpu_to_le32(tx_seq_32);

	if (key_type == KEY_TKIP) {
		/*
		 * We get the key in the following form:
		 * TKIP (16 bytes) - TX MIC (8 bytes) - RX MIC (8 bytes)
		 * but the target is expecting:
		 * TKIP - RX MIC - TX MIC
		 */
		memcpy(cmd->key, key, 16);
		memcpy(cmd->key + 16, key + 24, 8);
		memcpy(cmd->key + 24, key + 16, 8);
	} else {
		memcpy(cmd->key, key, key_size);
	}

	wl1271_dump(DEBUG_CRYPT, "TARGET AP KEY: ", cmd, sizeof(*cmd));

	ret = wl1271_cmd_send(wl, CMD_SET_KEYS, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_warning("could not set ap keys");
		goto out;
	}

out:
	kfree(cmd);
	return ret;
}