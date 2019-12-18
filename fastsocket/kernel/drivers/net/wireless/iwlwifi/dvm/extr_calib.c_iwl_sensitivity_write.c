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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_sensitivity_data {int dummy; } ;
struct iwl_sensitivity_cmd {int /*<<< orphan*/ * table; int /*<<< orphan*/  control; } ;
struct iwl_priv {int /*<<< orphan*/ * sensitivity_tbl; struct iwl_sensitivity_data sensitivity_data; } ;
struct iwl_host_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int HD_TABLE_SIZE ; 
 int /*<<< orphan*/  IWL_DEBUG_CALIB (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  SENSITIVITY_CMD ; 
 int /*<<< orphan*/  SENSITIVITY_CMD_CONTROL_WORK_TABLE ; 
 int iwl_dvm_send_cmd (struct iwl_priv*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  iwl_prepare_legacy_sensitivity_tbl (struct iwl_priv*,struct iwl_sensitivity_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct iwl_sensitivity_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_sensitivity_write(struct iwl_priv *priv)
{
	struct iwl_sensitivity_cmd cmd;
	struct iwl_sensitivity_data *data = NULL;
	struct iwl_host_cmd cmd_out = {
		.id = SENSITIVITY_CMD,
		.len = { sizeof(struct iwl_sensitivity_cmd), },
		.flags = CMD_ASYNC,
		.data = { &cmd, },
	};

	data = &(priv->sensitivity_data);

	memset(&cmd, 0, sizeof(cmd));

	iwl_prepare_legacy_sensitivity_tbl(priv, data, &cmd.table[0]);

	/* Update uCode's "work" table, and copy it to DSP */
	cmd.control = SENSITIVITY_CMD_CONTROL_WORK_TABLE;

	/* Don't send command to uCode if nothing has changed */
	if (!memcmp(&cmd.table[0], &(priv->sensitivity_tbl[0]),
		    sizeof(u16)*HD_TABLE_SIZE)) {
		IWL_DEBUG_CALIB(priv, "No change in SENSITIVITY_CMD\n");
		return 0;
	}

	/* Copy table for comparison next time */
	memcpy(&(priv->sensitivity_tbl[0]), &(cmd.table[0]),
	       sizeof(u16)*HD_TABLE_SIZE);

	return iwl_dvm_send_cmd(priv, &cmd_out);
}