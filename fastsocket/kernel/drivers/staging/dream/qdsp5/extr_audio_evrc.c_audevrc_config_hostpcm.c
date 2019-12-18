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
struct audplay_cmd_hpcm_buf_cfg {int max_buffers; int hostpcm_config; int feedback_frequency; scalar_t__ partition_number; scalar_t__ byte_swap; int /*<<< orphan*/  cmd_id; } ;
struct audio {int dummy; } ;
typedef  int /*<<< orphan*/  cfg_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPLAY_CMD_HPCM_BUF_CFG ; 
 int /*<<< orphan*/  audplay_send_queue0 (struct audio*,struct audplay_cmd_hpcm_buf_cfg*,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static void audevrc_config_hostpcm(struct audio *audio)
{
	struct audplay_cmd_hpcm_buf_cfg cfg_cmd;

	dprintk("audevrc_config_hostpcm()\n");
	cfg_cmd.cmd_id = AUDPLAY_CMD_HPCM_BUF_CFG;
	cfg_cmd.max_buffers = 1;
	cfg_cmd.byte_swap = 0;
	cfg_cmd.hostpcm_config = (0x8000) | (0x4000);
	cfg_cmd.feedback_frequency = 1;
	cfg_cmd.partition_number = 0;
	audplay_send_queue0(audio, &cfg_cmd, sizeof(cfg_cmd));

}