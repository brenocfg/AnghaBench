#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct iwl_sensitivity_data {int dummy; } ;
struct iwl_priv {int /*<<< orphan*/ * enhance_sensitivity_tbl; int /*<<< orphan*/ * sensitivity_tbl; TYPE_2__* cfg; struct iwl_sensitivity_data sensitivity_data; } ;
struct iwl_host_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;
struct iwl_enhance_sensitivity_cmd {int /*<<< orphan*/ * enhance_table; int /*<<< orphan*/  control; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {scalar_t__ hd_v2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int ENHANCE_HD_TABLE_ENTRIES ; 
 int /*<<< orphan*/  HD_CCK_NON_SQUARE_DET_INTERCEPT_DATA_V1 ; 
 int /*<<< orphan*/  HD_CCK_NON_SQUARE_DET_INTERCEPT_DATA_V2 ; 
 size_t HD_CCK_NON_SQUARE_DET_INTERCEPT_INDEX ; 
 int /*<<< orphan*/  HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V1 ; 
 int /*<<< orphan*/  HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V2 ; 
 size_t HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_INDEX ; 
 int /*<<< orphan*/  HD_CCK_NON_SQUARE_DET_SLOPE_DATA_V1 ; 
 int /*<<< orphan*/  HD_CCK_NON_SQUARE_DET_SLOPE_DATA_V2 ; 
 size_t HD_CCK_NON_SQUARE_DET_SLOPE_INDEX ; 
 int /*<<< orphan*/  HD_CCK_NON_SQUARE_DET_SLOPE_MRC_DATA_V1 ; 
 int /*<<< orphan*/  HD_CCK_NON_SQUARE_DET_SLOPE_MRC_DATA_V2 ; 
 size_t HD_CCK_NON_SQUARE_DET_SLOPE_MRC_INDEX ; 
 int /*<<< orphan*/  HD_CORR_11_INSTEAD_OF_CORR_9_EN_DATA_V1 ; 
 int /*<<< orphan*/  HD_CORR_11_INSTEAD_OF_CORR_9_EN_DATA_V2 ; 
 size_t HD_CORR_11_INSTEAD_OF_CORR_9_EN_INDEX ; 
 int /*<<< orphan*/  HD_INA_NON_SQUARE_DET_CCK_DATA_V1 ; 
 int /*<<< orphan*/  HD_INA_NON_SQUARE_DET_CCK_DATA_V2 ; 
 size_t HD_INA_NON_SQUARE_DET_CCK_INDEX ; 
 int /*<<< orphan*/  HD_INA_NON_SQUARE_DET_OFDM_DATA_V1 ; 
 int /*<<< orphan*/  HD_INA_NON_SQUARE_DET_OFDM_DATA_V2 ; 
 size_t HD_INA_NON_SQUARE_DET_OFDM_INDEX ; 
 int /*<<< orphan*/  HD_OFDM_NON_SQUARE_DET_INTERCEPT_DATA_V1 ; 
 int /*<<< orphan*/  HD_OFDM_NON_SQUARE_DET_INTERCEPT_DATA_V2 ; 
 size_t HD_OFDM_NON_SQUARE_DET_INTERCEPT_INDEX ; 
 int /*<<< orphan*/  HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V1 ; 
 int /*<<< orphan*/  HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V2 ; 
 size_t HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_INDEX ; 
 int /*<<< orphan*/  HD_OFDM_NON_SQUARE_DET_SLOPE_DATA_V1 ; 
 int /*<<< orphan*/  HD_OFDM_NON_SQUARE_DET_SLOPE_DATA_V2 ; 
 size_t HD_OFDM_NON_SQUARE_DET_SLOPE_INDEX ; 
 int /*<<< orphan*/  HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_DATA_V1 ; 
 int /*<<< orphan*/  HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_DATA_V2 ; 
 size_t HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_INDEX ; 
 int HD_TABLE_SIZE ; 
 int /*<<< orphan*/  IWL_DEBUG_CALIB (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  SENSITIVITY_CMD ; 
 int /*<<< orphan*/  SENSITIVITY_CMD_CONTROL_WORK_TABLE ; 
 int iwl_dvm_send_cmd (struct iwl_priv*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  iwl_prepare_legacy_sensitivity_tbl (struct iwl_priv*,struct iwl_sensitivity_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct iwl_enhance_sensitivity_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_enhance_sensitivity_write(struct iwl_priv *priv)
{
	struct iwl_enhance_sensitivity_cmd cmd;
	struct iwl_sensitivity_data *data = NULL;
	struct iwl_host_cmd cmd_out = {
		.id = SENSITIVITY_CMD,
		.len = { sizeof(struct iwl_enhance_sensitivity_cmd), },
		.flags = CMD_ASYNC,
		.data = { &cmd, },
	};

	data = &(priv->sensitivity_data);

	memset(&cmd, 0, sizeof(cmd));

	iwl_prepare_legacy_sensitivity_tbl(priv, data, &cmd.enhance_table[0]);

	if (priv->cfg->base_params->hd_v2) {
		cmd.enhance_table[HD_INA_NON_SQUARE_DET_OFDM_INDEX] =
			HD_INA_NON_SQUARE_DET_OFDM_DATA_V2;
		cmd.enhance_table[HD_INA_NON_SQUARE_DET_CCK_INDEX] =
			HD_INA_NON_SQUARE_DET_CCK_DATA_V2;
		cmd.enhance_table[HD_CORR_11_INSTEAD_OF_CORR_9_EN_INDEX] =
			HD_CORR_11_INSTEAD_OF_CORR_9_EN_DATA_V2;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_INDEX] =
			HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_DATA_V2;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_INDEX] =
			HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V2;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_SLOPE_INDEX] =
			HD_OFDM_NON_SQUARE_DET_SLOPE_DATA_V2;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_INTERCEPT_INDEX] =
			HD_OFDM_NON_SQUARE_DET_INTERCEPT_DATA_V2;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_SLOPE_MRC_INDEX] =
			HD_CCK_NON_SQUARE_DET_SLOPE_MRC_DATA_V2;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_INDEX] =
			HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V2;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_SLOPE_INDEX] =
			HD_CCK_NON_SQUARE_DET_SLOPE_DATA_V2;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_INTERCEPT_INDEX] =
			HD_CCK_NON_SQUARE_DET_INTERCEPT_DATA_V2;
	} else {
		cmd.enhance_table[HD_INA_NON_SQUARE_DET_OFDM_INDEX] =
			HD_INA_NON_SQUARE_DET_OFDM_DATA_V1;
		cmd.enhance_table[HD_INA_NON_SQUARE_DET_CCK_INDEX] =
			HD_INA_NON_SQUARE_DET_CCK_DATA_V1;
		cmd.enhance_table[HD_CORR_11_INSTEAD_OF_CORR_9_EN_INDEX] =
			HD_CORR_11_INSTEAD_OF_CORR_9_EN_DATA_V1;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_INDEX] =
			HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_DATA_V1;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_INDEX] =
			HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V1;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_SLOPE_INDEX] =
			HD_OFDM_NON_SQUARE_DET_SLOPE_DATA_V1;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_INTERCEPT_INDEX] =
			HD_OFDM_NON_SQUARE_DET_INTERCEPT_DATA_V1;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_SLOPE_MRC_INDEX] =
			HD_CCK_NON_SQUARE_DET_SLOPE_MRC_DATA_V1;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_INDEX] =
			HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V1;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_SLOPE_INDEX] =
			HD_CCK_NON_SQUARE_DET_SLOPE_DATA_V1;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_INTERCEPT_INDEX] =
			HD_CCK_NON_SQUARE_DET_INTERCEPT_DATA_V1;
	}

	/* Update uCode's "work" table, and copy it to DSP */
	cmd.control = SENSITIVITY_CMD_CONTROL_WORK_TABLE;

	/* Don't send command to uCode if nothing has changed */
	if (!memcmp(&cmd.enhance_table[0], &(priv->sensitivity_tbl[0]),
		    sizeof(u16)*HD_TABLE_SIZE) &&
	    !memcmp(&cmd.enhance_table[HD_INA_NON_SQUARE_DET_OFDM_INDEX],
		    &(priv->enhance_sensitivity_tbl[0]),
		    sizeof(u16)*ENHANCE_HD_TABLE_ENTRIES)) {
		IWL_DEBUG_CALIB(priv, "No change in SENSITIVITY_CMD\n");
		return 0;
	}

	/* Copy table for comparison next time */
	memcpy(&(priv->sensitivity_tbl[0]), &(cmd.enhance_table[0]),
	       sizeof(u16)*HD_TABLE_SIZE);
	memcpy(&(priv->enhance_sensitivity_tbl[0]),
	       &(cmd.enhance_table[HD_INA_NON_SQUARE_DET_OFDM_INDEX]),
	       sizeof(u16)*ENHANCE_HD_TABLE_ENTRIES);

	return iwl_dvm_send_cmd(priv, &cmd_out);
}