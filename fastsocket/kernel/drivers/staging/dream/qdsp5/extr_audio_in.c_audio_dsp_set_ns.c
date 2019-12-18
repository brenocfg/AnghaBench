#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ns_params; } ;
struct audio_in {TYPE_1__ ns; scalar_t__ ns_enable; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {int cmd_id; int ec_mode_new; int dens_gamma_n; int dens_nfe_block_size; int dens_limit_ns; int dens_limit_ns_d; int wb_gamma_e; int wb_gamma_n; } ;
typedef  TYPE_2__ audpreproc_cmd_cfg_ns_params ;

/* Variables and functions */
 int AUDPREPROC_CMD_CFG_NS_PARAMS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_CNI_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_DES_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_FEHI_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_FNE_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_HB_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_HB_ENA ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_NEHI_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_NLES_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_NLMS_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_NLPP_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_NS_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_NS_ENA ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_PCD_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_PRENLMS_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_VA_DIS ; 
 int AUDPREPROC_CMD_EC_MODE_NEW_VA_ENA ; 
 int audio_send_queue_pre (struct audio_in*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

__attribute__((used)) static int audio_dsp_set_ns(struct audio_in *audio)
{
	audpreproc_cmd_cfg_ns_params cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd_id = AUDPREPROC_CMD_CFG_NS_PARAMS;

	if (audio->ns_enable) {
		/* cmd.ec_mode_new is fixed as 0x0064 when enable from sample code */
		cmd.ec_mode_new =
			AUDPREPROC_CMD_EC_MODE_NEW_NS_ENA |
			AUDPREPROC_CMD_EC_MODE_NEW_HB_ENA |
			AUDPREPROC_CMD_EC_MODE_NEW_VA_ENA;
		memcpy(&cmd.dens_gamma_n, &audio->ns.ns_params,
			sizeof(audio->ns.ns_params));
	} else {
		cmd.ec_mode_new =
			AUDPREPROC_CMD_EC_MODE_NEW_NLMS_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_DES_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_NS_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_CNI_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_NLES_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_HB_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_VA_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_PCD_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_FEHI_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_NEHI_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_NLPP_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_FNE_DIS |
			AUDPREPROC_CMD_EC_MODE_NEW_PRENLMS_DIS;
	}
#if DEBUG
	pr_info("cmd_id = 0x%04x\n", cmd.cmd_id);
	pr_info("ec_mode_new = 0x%04x\n", cmd.ec_mode_new);
	pr_info("dens_gamma_n = 0x%04x\n", cmd.dens_gamma_n);
	pr_info("dens_nfe_block_size = 0x%04x\n", cmd.dens_nfe_block_size);
	pr_info("dens_limit_ns = 0x%04x\n", cmd.dens_limit_ns);
	pr_info("dens_limit_ns_d = 0x%04x\n", cmd.dens_limit_ns_d);
	pr_info("wb_gamma_e = 0x%04x\n", cmd.wb_gamma_e);
	pr_info("wb_gamma_n = 0x%04x\n", cmd.wb_gamma_n);
#endif
	return audio_send_queue_pre(audio, &cmd, sizeof(cmd));
}