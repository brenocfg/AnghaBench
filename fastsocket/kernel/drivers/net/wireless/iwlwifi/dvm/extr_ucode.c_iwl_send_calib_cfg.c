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
struct iwl_priv {int dummy; } ;
struct iwl_host_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {void* send_res; void* start; void* is_enable; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; TYPE_2__ once; } ;
struct iwl_calib_cfg_cmd {TYPE_1__ ucd_calib_cfg; } ;
typedef  int /*<<< orphan*/  calib_cfg_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CALIBRATION_CFG_CMD ; 
 int /*<<< orphan*/  IWL_CALIB_CFG_FLAG_SEND_COMPLETE_NTFY_MSK ; 
 void* IWL_CALIB_INIT_CFG_ALL ; 
 int iwl_dvm_send_cmd (struct iwl_priv*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  memset (struct iwl_calib_cfg_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_send_calib_cfg(struct iwl_priv *priv)
{
	struct iwl_calib_cfg_cmd calib_cfg_cmd;
	struct iwl_host_cmd cmd = {
		.id = CALIBRATION_CFG_CMD,
		.len = { sizeof(struct iwl_calib_cfg_cmd), },
		.data = { &calib_cfg_cmd, },
	};

	memset(&calib_cfg_cmd, 0, sizeof(calib_cfg_cmd));
	calib_cfg_cmd.ucd_calib_cfg.once.is_enable = IWL_CALIB_INIT_CFG_ALL;
	calib_cfg_cmd.ucd_calib_cfg.once.start = IWL_CALIB_INIT_CFG_ALL;
	calib_cfg_cmd.ucd_calib_cfg.once.send_res = IWL_CALIB_INIT_CFG_ALL;
	calib_cfg_cmd.ucd_calib_cfg.flags =
		IWL_CALIB_CFG_FLAG_SEND_COMPLETE_NTFY_MSK;

	return iwl_dvm_send_cmd(priv, &cmd);
}