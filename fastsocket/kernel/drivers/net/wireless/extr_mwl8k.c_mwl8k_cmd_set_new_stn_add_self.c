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
struct TYPE_2__ {void* length; void* code; } ;
struct mwl8k_cmd_set_new_stn {TYPE_1__ header; int /*<<< orphan*/  mac_addr; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_SET_NEW_STN ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_set_new_stn*) ; 
 struct mwl8k_cmd_set_new_stn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mwl8k_post_pervif_cmd (struct ieee80211_hw*,struct ieee80211_vif*,TYPE_1__*) ; 

__attribute__((used)) static int mwl8k_cmd_set_new_stn_add_self(struct ieee80211_hw *hw,
					  struct ieee80211_vif *vif)
{
	struct mwl8k_cmd_set_new_stn *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_NEW_STN);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	memcpy(cmd->mac_addr, vif->addr, ETH_ALEN);

	rc = mwl8k_post_pervif_cmd(hw, vif, &cmd->header);
	kfree(cmd);

	return rc;
}