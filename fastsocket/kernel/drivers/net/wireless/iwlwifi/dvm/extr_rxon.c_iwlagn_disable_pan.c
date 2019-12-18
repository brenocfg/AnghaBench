#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iwl_rxon_context {int /*<<< orphan*/  rxon_cmd; } ;
struct iwl_rxon_cmd {int /*<<< orphan*/  dev_type; int /*<<< orphan*/  filter_flags; } ;
struct iwl_priv {int /*<<< orphan*/  notif_wait; } ;
struct iwl_notification_wait {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,...) ; 
#define  REPLY_WIPAN_DEACTIVATION_COMPLETE 128 
 int /*<<< orphan*/  RXON_DEV_TYPE_P2P ; 
 int /*<<< orphan*/  RXON_FILTER_ASSOC_MSK ; 
 int iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_rxon_cmd*) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwlagn_disable_pan(struct iwl_priv *priv,
			      struct iwl_rxon_context *ctx,
			      struct iwl_rxon_cmd *send)
{
	struct iwl_notification_wait disable_wait;
	__le32 old_filter = send->filter_flags;
	u8 old_dev_type = send->dev_type;
	int ret;
	static const u8 deactivate_cmd[] = {
		REPLY_WIPAN_DEACTIVATION_COMPLETE
	};

	iwl_init_notification_wait(&priv->notif_wait, &disable_wait,
				   deactivate_cmd, ARRAY_SIZE(deactivate_cmd),
				   NULL, NULL);

	send->filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	send->dev_type = RXON_DEV_TYPE_P2P;
	ret = iwl_dvm_send_cmd_pdu(priv, ctx->rxon_cmd,
				CMD_SYNC, sizeof(*send), send);

	send->filter_flags = old_filter;
	send->dev_type = old_dev_type;

	if (ret) {
		IWL_ERR(priv, "Error disabling PAN (%d)\n", ret);
		iwl_remove_notification(&priv->notif_wait, &disable_wait);
	} else {
		ret = iwl_wait_notification(&priv->notif_wait,
					    &disable_wait, HZ);
		if (ret)
			IWL_ERR(priv, "Timed out waiting for PAN disable\n");
	}

	return ret;
}