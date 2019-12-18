#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_8__ {void* length; void* code; } ;
struct TYPE_6__ {int reset_seq_no_flag; int param_info; void* flags; void* curr_seq_no; int /*<<< orphan*/  tid; int /*<<< orphan*/  peer_mac_addr; int /*<<< orphan*/  queue_id; void* window_size; void* bar_thrs; } ;
struct mwl8k_cmd_bastream {TYPE_4__ header; TYPE_2__ create_params; void* action; } ;
struct mwl8k_ampdu_stream {int /*<<< orphan*/  tid; TYPE_3__* sta; int /*<<< orphan*/  idx; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct TYPE_5__ {int ampdu_factor; int ampdu_density; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; TYPE_1__ ht_cap; } ;

/* Variables and functions */
 int BASTREAM_FLAG_DIRECTION_UPSTREAM ; 
 int BASTREAM_FLAG_IMMEDIATE_TYPE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_HT_AMPDU_PARM_DENSITY ; 
 int IEEE80211_HT_AMPDU_PARM_FACTOR ; 
 int MWL8K_BA_CREATE ; 
 int MWL8K_CMD_BASTREAM ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_bastream*) ; 
 struct mwl8k_cmd_bastream* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mwl8k_post_pervif_cmd (struct ieee80211_hw*,struct ieee80211_vif*,TYPE_4__*) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwl8k_create_ba(struct ieee80211_hw *hw, struct mwl8k_ampdu_stream *stream,
		u8 buf_size, struct ieee80211_vif *vif)
{
	struct mwl8k_cmd_bastream *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;


	cmd->header.code = cpu_to_le16(MWL8K_CMD_BASTREAM);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));

	cmd->action = cpu_to_le32(MWL8K_BA_CREATE);

	cmd->create_params.bar_thrs = cpu_to_le32((u32)buf_size);
	cmd->create_params.window_size = cpu_to_le32((u32)buf_size);
	cmd->create_params.queue_id = stream->idx;

	memcpy(cmd->create_params.peer_mac_addr, stream->sta->addr, ETH_ALEN);
	cmd->create_params.tid = stream->tid;
	cmd->create_params.curr_seq_no = cpu_to_le16(0);
	cmd->create_params.reset_seq_no_flag = 1;

	cmd->create_params.param_info =
		(stream->sta->ht_cap.ampdu_factor &
		 IEEE80211_HT_AMPDU_PARM_FACTOR) |
		((stream->sta->ht_cap.ampdu_density << 2) &
		 IEEE80211_HT_AMPDU_PARM_DENSITY);

	cmd->create_params.flags =
		cpu_to_le32(BASTREAM_FLAG_IMMEDIATE_TYPE |
					BASTREAM_FLAG_DIRECTION_UPSTREAM);

	rc = mwl8k_post_pervif_cmd(hw, vif, &cmd->header);

	wiphy_debug(hw->wiphy, "Created a BA stream for %pM : tid %d\n",
		stream->sta->addr, stream->tid);
	kfree(cmd);

	return rc;
}