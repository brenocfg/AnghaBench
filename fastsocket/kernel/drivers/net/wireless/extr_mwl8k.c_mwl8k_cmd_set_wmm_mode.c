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
struct mwl8k_priv {int wmm_enabled; } ;
struct TYPE_2__ {void* length; void* code; } ;
struct mwl8k_cmd_set_wmm_mode {TYPE_1__ header; void* action; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_SET_WMM_MODE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_set_wmm_mode*) ; 
 struct mwl8k_cmd_set_wmm_mode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_1__*) ; 

__attribute__((used)) static int mwl8k_cmd_set_wmm_mode(struct ieee80211_hw *hw, bool enable)
{
	struct mwl8k_priv *priv = hw->priv;
	struct mwl8k_cmd_set_wmm_mode *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_WMM_MODE);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le16(!!enable);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kfree(cmd);

	if (!rc)
		priv->wmm_enabled = enable;

	return rc;
}