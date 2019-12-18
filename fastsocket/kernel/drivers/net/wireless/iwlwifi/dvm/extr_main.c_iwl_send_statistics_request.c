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
typedef  int u8 ;
struct iwl_statistics_cmd {int /*<<< orphan*/  configuration_flags; } ;
struct iwl_priv {int dummy; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int CMD_SYNC ; 
 int /*<<< orphan*/  IWL_STATS_CONF_CLEAR_STATS ; 
 int /*<<< orphan*/  REPLY_STATISTICS_CMD ; 
 int iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int,int,struct iwl_statistics_cmd*) ; 

int iwl_send_statistics_request(struct iwl_priv *priv, u8 flags, bool clear)
{
	struct iwl_statistics_cmd statistics_cmd = {
		.configuration_flags =
			clear ? IWL_STATS_CONF_CLEAR_STATS : 0,
	};

	if (flags & CMD_ASYNC)
		return iwl_dvm_send_cmd_pdu(priv, REPLY_STATISTICS_CMD,
					CMD_ASYNC,
					sizeof(struct iwl_statistics_cmd),
					&statistics_cmd);
	else
		return iwl_dvm_send_cmd_pdu(priv, REPLY_STATISTICS_CMD,
					CMD_SYNC,
					sizeof(struct iwl_statistics_cmd),
					&statistics_cmd);
}