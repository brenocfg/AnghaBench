#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct mwl8k_priv {scalar_t__ ap_fw; } ;
struct TYPE_6__ {void* length; void* code; } ;
struct TYPE_5__ {void* txq; void* aifs; void* log_cw_min; void* log_cw_max; } ;
struct TYPE_4__ {void* txq; void* aifs; void* log_cw_min; void* log_cw_max; } ;
struct mwl8k_cmd_set_edca_params {TYPE_3__ header; TYPE_2__ sta; TYPE_1__ ap; void* txop; void* action; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
typedef  void* __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_SET_EDCA_PARAMS ; 
 int MWL8K_SET_EDCA_ALL ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 scalar_t__ ilog2 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_set_edca_params*) ; 
 struct mwl8k_cmd_set_edca_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_3__*) ; 

__attribute__((used)) static int
mwl8k_cmd_set_edca_params(struct ieee80211_hw *hw, __u8 qnum,
			  __u16 cw_min, __u16 cw_max,
			  __u8 aifs, __u16 txop)
{
	struct mwl8k_priv *priv = hw->priv;
	struct mwl8k_cmd_set_edca_params *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_EDCA_PARAMS);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le16(MWL8K_SET_EDCA_ALL);
	cmd->txop = cpu_to_le16(txop);
	if (priv->ap_fw) {
		cmd->ap.log_cw_max = cpu_to_le32(ilog2(cw_max + 1));
		cmd->ap.log_cw_min = cpu_to_le32(ilog2(cw_min + 1));
		cmd->ap.aifs = aifs;
		cmd->ap.txq = qnum;
	} else {
		cmd->sta.log_cw_max = (u8)ilog2(cw_max + 1);
		cmd->sta.log_cw_min = (u8)ilog2(cw_min + 1);
		cmd->sta.aifs = aifs;
		cmd->sta.txq = qnum;
	}

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kfree(cmd);

	return rc;
}