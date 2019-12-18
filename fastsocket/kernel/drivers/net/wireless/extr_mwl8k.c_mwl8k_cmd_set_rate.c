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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {void* length; void* code; } ;
struct mwl8k_cmd_set_rate {TYPE_1__ header; int /*<<< orphan*/  mcs_set; int /*<<< orphan*/  legacy_rates; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_SET_RATE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_set_rate*) ; 
 struct mwl8k_cmd_set_rate* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legacy_rate_mask_to_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_1__*) ; 

__attribute__((used)) static int
mwl8k_cmd_set_rate(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		   u32 legacy_rate_mask, u8 *mcs_rates)
{
	struct mwl8k_cmd_set_rate *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_RATE);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	legacy_rate_mask_to_array(cmd->legacy_rates, legacy_rate_mask);
	memcpy(cmd->mcs_set, mcs_rates, 16);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kfree(cmd);

	return rc;
}