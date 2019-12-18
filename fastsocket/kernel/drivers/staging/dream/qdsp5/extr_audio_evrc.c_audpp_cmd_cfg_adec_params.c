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
struct TYPE_2__ {int length; int input_sampling_frequency; int /*<<< orphan*/  dec_id; int /*<<< orphan*/  cmd_id; } ;
struct audpp_cmd_cfg_adec_params_evrc {int /*<<< orphan*/  stereo_cfg; TYPE_1__ common; } ;
struct audio {int /*<<< orphan*/  dec_id; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPP_CMD_CFG_ADEC_PARAMS ; 
 int /*<<< orphan*/  AUDPP_CMD_PCM_INTF_MONO_V ; 
 int /*<<< orphan*/  audpp_send_queue2 (struct audpp_cmd_cfg_adec_params_evrc*,int) ; 
 int /*<<< orphan*/  memset (struct audpp_cmd_cfg_adec_params_evrc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void audpp_cmd_cfg_adec_params(struct audio *audio)
{
	struct audpp_cmd_cfg_adec_params_evrc cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.common.cmd_id = AUDPP_CMD_CFG_ADEC_PARAMS;
	cmd.common.length = sizeof(cmd);
	cmd.common.dec_id = audio->dec_id;
	cmd.common.input_sampling_frequency = 8000;
	cmd.stereo_cfg = AUDPP_CMD_PCM_INTF_MONO_V;

	audpp_send_queue2(&cmd, sizeof(cmd));
}