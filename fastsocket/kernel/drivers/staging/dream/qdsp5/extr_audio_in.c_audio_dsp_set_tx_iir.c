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
struct audpre_cmd_iir_config_type {int /*<<< orphan*/  active_flag; int /*<<< orphan*/  cmd_id; int /*<<< orphan*/  iir_params; int /*<<< orphan*/  num_bands; } ;
struct TYPE_2__ {int /*<<< orphan*/  iir_params; int /*<<< orphan*/  num_bands; } ;
struct audio_in {TYPE_1__ iir; scalar_t__ iir_enable; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPREPROC_CMD_CFG_IIR_TUNING_FILTER_PARAMS ; 
 int /*<<< orphan*/  AUDPREPROC_CMD_IIR_ACTIVE_FLAG_DIS ; 
 int /*<<< orphan*/  AUDPREPROC_CMD_IIR_ACTIVE_FLAG_ENA ; 
 int audio_send_queue_pre (struct audio_in*,struct audpre_cmd_iir_config_type*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct audpre_cmd_iir_config_type*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audio_dsp_set_tx_iir(struct audio_in *audio)
{
	struct audpre_cmd_iir_config_type cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd_id = AUDPREPROC_CMD_CFG_IIR_TUNING_FILTER_PARAMS;

	if (audio->iir_enable) {
		cmd.active_flag = AUDPREPROC_CMD_IIR_ACTIVE_FLAG_ENA;
		cmd.num_bands = audio->iir.num_bands;
		memcpy(&cmd.iir_params, &audio->iir.iir_params,
			sizeof(audio->iir.iir_params));
	} else {
		cmd.active_flag = AUDPREPROC_CMD_IIR_ACTIVE_FLAG_DIS;
	}
#if DEBUG
	pr_info("cmd_id = 0x%04x\n", cmd.cmd_id);
	pr_info("active_flag = 0x%04x\n", cmd.active_flag);
#endif
	return audio_send_queue_pre(audio, &cmd, sizeof(cmd));
}