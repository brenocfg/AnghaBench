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
struct audio {int /*<<< orphan*/  out_sample_rate; int /*<<< orphan*/  dec_id; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {int /*<<< orphan*/  input_sampling_frequency; int /*<<< orphan*/  dec_id; int /*<<< orphan*/  length; int /*<<< orphan*/  cmd_id; } ;
struct TYPE_6__ {TYPE_1__ common; } ;
typedef  TYPE_2__ audpp_cmd_cfg_adec_params_mp3 ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPP_CMD_CFG_ADEC_PARAMS ; 
 int /*<<< orphan*/  AUDPP_CMD_CFG_ADEC_PARAMS_MP3_LEN ; 
 int /*<<< orphan*/  audpp_send_queue2 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void audpp_cmd_cfg_adec_params(struct audio *audio)
{
	audpp_cmd_cfg_adec_params_mp3 cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.common.cmd_id = AUDPP_CMD_CFG_ADEC_PARAMS;
	cmd.common.length = AUDPP_CMD_CFG_ADEC_PARAMS_MP3_LEN;
	cmd.common.dec_id = audio->dec_id;
	cmd.common.input_sampling_frequency = audio->out_sample_rate;

	audpp_send_queue2(&cmd, sizeof(cmd));
}