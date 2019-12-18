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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/ * agc_params; } ;
struct audio_in {TYPE_1__ agc; scalar_t__ agc_enable; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {int cmd_id; int tx_agc_param_mask; int tx_agc_enable_flag; int static_gain; int param_mask; int aig_attackk; int adaptive_gain_flag; int expander_th; int expander_slope; int compressor_th; int compressor_slope; int aig_leak_down; int aig_leak_up; int aig_max; int aig_min; int aig_releasek; int aig_leakrate_fast; int aig_leakrate_slow; int attackk_msw; int attackk_lsw; int delay; int releasek_msw; int releasek_lsw; int rms_tav; } ;
typedef  TYPE_2__ audpreproc_cmd_cfg_agc_params ;

/* Variables and functions */
 int AUDPREPROC_CMD_CFG_AGC_PARAMS ; 
 int AUDPREPROC_CMD_PARAM_MASK_AIG_ATTACKK ; 
 int AUDPREPROC_CMD_PARAM_MASK_AIG_MAX ; 
 int AUDPREPROC_CMD_PARAM_MASK_AIG_MIN ; 
 int AUDPREPROC_CMD_PARAM_MASK_AIG_RELEASEK ; 
 int AUDPREPROC_CMD_PARAM_MASK_ATTACKK ; 
 int AUDPREPROC_CMD_PARAM_MASK_DELAY ; 
 int AUDPREPROC_CMD_PARAM_MASK_LEAKRATE_FAST ; 
 int AUDPREPROC_CMD_PARAM_MASK_LEAKRATE_SLOW ; 
 int AUDPREPROC_CMD_PARAM_MASK_LEAK_DOWN ; 
 int AUDPREPROC_CMD_PARAM_MASK_LEAK_UP ; 
 int AUDPREPROC_CMD_PARAM_MASK_RELEASEK ; 
 int AUDPREPROC_CMD_PARAM_MASK_RMS_TAY ; 
 int AUDPREPROC_CMD_TX_AGC_ENA_FLAG_DIS ; 
 int AUDPREPROC_CMD_TX_AGC_ENA_FLAG_ENA ; 
 int AUDPREPROC_CMD_TX_AGC_PARAM_MASK_COMP_AIG_FLAG ; 
 int AUDPREPROC_CMD_TX_AGC_PARAM_MASK_COMP_SLOPE ; 
 int AUDPREPROC_CMD_TX_AGC_PARAM_MASK_COMP_STATIC_GAIN ; 
 int AUDPREPROC_CMD_TX_AGC_PARAM_MASK_COMP_TH ; 
 int AUDPREPROC_CMD_TX_AGC_PARAM_MASK_EXP_SLOPE ; 
 int AUDPREPROC_CMD_TX_AGC_PARAM_MASK_EXP_TH ; 
 int AUDPREPROC_CMD_TX_AGC_PARAM_MASK_TX_AGC_ENA_FLAG ; 
 int audio_send_queue_pre (struct audio_in*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

__attribute__((used)) static int audio_dsp_set_agc(struct audio_in *audio)
{
	audpreproc_cmd_cfg_agc_params cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd_id = AUDPREPROC_CMD_CFG_AGC_PARAMS;

	if (audio->agc_enable) {
		/* cmd.tx_agc_param_mask = 0xFE00 from sample code */
		cmd.tx_agc_param_mask =
		(1 << AUDPREPROC_CMD_TX_AGC_PARAM_MASK_COMP_SLOPE) |
		(1 << AUDPREPROC_CMD_TX_AGC_PARAM_MASK_COMP_TH) |
		(1 << AUDPREPROC_CMD_TX_AGC_PARAM_MASK_EXP_SLOPE) |
		(1 << AUDPREPROC_CMD_TX_AGC_PARAM_MASK_EXP_TH) |
		(1 << AUDPREPROC_CMD_TX_AGC_PARAM_MASK_COMP_AIG_FLAG) |
		(1 << AUDPREPROC_CMD_TX_AGC_PARAM_MASK_COMP_STATIC_GAIN) |
		(1 << AUDPREPROC_CMD_TX_AGC_PARAM_MASK_TX_AGC_ENA_FLAG);
		cmd.tx_agc_enable_flag =
			AUDPREPROC_CMD_TX_AGC_ENA_FLAG_ENA;
		memcpy(&cmd.static_gain, &audio->agc.agc_params[0],
			sizeof(uint16_t) * 6);
		/* cmd.param_mask = 0xFFF0 from sample code */
		cmd.param_mask =
			(1 << AUDPREPROC_CMD_PARAM_MASK_RMS_TAY) |
			(1 << AUDPREPROC_CMD_PARAM_MASK_RELEASEK) |
			(1 << AUDPREPROC_CMD_PARAM_MASK_DELAY) |
			(1 << AUDPREPROC_CMD_PARAM_MASK_ATTACKK) |
			(1 << AUDPREPROC_CMD_PARAM_MASK_LEAKRATE_SLOW) |
			(1 << AUDPREPROC_CMD_PARAM_MASK_LEAKRATE_FAST) |
			(1 << AUDPREPROC_CMD_PARAM_MASK_AIG_RELEASEK) |
			(1 << AUDPREPROC_CMD_PARAM_MASK_AIG_MIN) |
			(1 << AUDPREPROC_CMD_PARAM_MASK_AIG_MAX) |
			(1 << AUDPREPROC_CMD_PARAM_MASK_LEAK_UP) |
			(1 << AUDPREPROC_CMD_PARAM_MASK_LEAK_DOWN) |
			(1 << AUDPREPROC_CMD_PARAM_MASK_AIG_ATTACKK);
		memcpy(&cmd.aig_attackk, &audio->agc.agc_params[6],
			sizeof(uint16_t) * 14);

	} else {
		cmd.tx_agc_param_mask =
			(1 << AUDPREPROC_CMD_TX_AGC_PARAM_MASK_TX_AGC_ENA_FLAG);
		cmd.tx_agc_enable_flag =
			AUDPREPROC_CMD_TX_AGC_ENA_FLAG_DIS;
	}
#if DEBUG
	pr_info("cmd_id = 0x%04x\n", cmd.cmd_id);
	pr_info("tx_agc_param_mask = 0x%04x\n", cmd.tx_agc_param_mask);
	pr_info("tx_agc_enable_flag = 0x%04x\n", cmd.tx_agc_enable_flag);
	pr_info("static_gain = 0x%04x\n", cmd.static_gain);
	pr_info("adaptive_gain_flag = 0x%04x\n", cmd.adaptive_gain_flag);
	pr_info("expander_th = 0x%04x\n", cmd.expander_th);
	pr_info("expander_slope = 0x%04x\n", cmd.expander_slope);
	pr_info("compressor_th = 0x%04x\n", cmd.compressor_th);
	pr_info("compressor_slope = 0x%04x\n", cmd.compressor_slope);
	pr_info("param_mask = 0x%04x\n", cmd.param_mask);
	pr_info("aig_attackk = 0x%04x\n", cmd.aig_attackk);
	pr_info("aig_leak_down = 0x%04x\n", cmd.aig_leak_down);
	pr_info("aig_leak_up = 0x%04x\n", cmd.aig_leak_up);
	pr_info("aig_max = 0x%04x\n", cmd.aig_max);
	pr_info("aig_min = 0x%04x\n", cmd.aig_min);
	pr_info("aig_releasek = 0x%04x\n", cmd.aig_releasek);
	pr_info("aig_leakrate_fast = 0x%04x\n", cmd.aig_leakrate_fast);
	pr_info("aig_leakrate_slow = 0x%04x\n", cmd.aig_leakrate_slow);
	pr_info("attackk_msw = 0x%04x\n", cmd.attackk_msw);
	pr_info("attackk_lsw = 0x%04x\n", cmd.attackk_lsw);
	pr_info("delay = 0x%04x\n", cmd.delay);
	pr_info("releasek_msw = 0x%04x\n", cmd.releasek_msw);
	pr_info("releasek_lsw = 0x%04x\n", cmd.releasek_lsw);
	pr_info("rms_tav = 0x%04x\n", cmd.rms_tav);
#endif
	return audio_send_queue_pre(audio, &cmd, sizeof(cmd));
}