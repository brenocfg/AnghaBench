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
struct audio {int /*<<< orphan*/  out_channel_mode; int /*<<< orphan*/  out_sample_rate; int /*<<< orphan*/  out_weight; TYPE_1__* out; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {int write_buf1LSW; int write_buf1MSW; int write_buf2LSW; int write_buf2MSW; int weight_arm_to_rx; int /*<<< orphan*/  channel_mode; int /*<<< orphan*/  sample_rate; scalar_t__ partition_number_arm_to_dsp; int /*<<< orphan*/  weight_decoder_to_rx; int /*<<< orphan*/  arm_to_rx_flag; int /*<<< orphan*/  write_buf2_len; int /*<<< orphan*/  write_buf1_len; int /*<<< orphan*/  intf_type; int /*<<< orphan*/  config; int /*<<< orphan*/  object_num; int /*<<< orphan*/  cmd_id; } ;
typedef  TYPE_2__ audpp_cmd_pcm_intf ;
struct TYPE_5__ {int addr; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPP_CMD_PCM_INTF_2 ; 
 int /*<<< orphan*/  AUDPP_CMD_PCM_INTF_CONFIG_CMD_V ; 
 int /*<<< orphan*/  AUDPP_CMD_PCM_INTF_ENA_V ; 
 int /*<<< orphan*/  AUDPP_CMD_PCM_INTF_OBJECT_NUM ; 
 int /*<<< orphan*/  AUDPP_CMD_PCM_INTF_RX_ENA_ARMTODSP_V ; 
 int audpp_send_queue2 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int audio_dsp_out_enable(struct audio *audio, int yes)
{
	audpp_cmd_pcm_intf cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd_id	= AUDPP_CMD_PCM_INTF_2;
	cmd.object_num	= AUDPP_CMD_PCM_INTF_OBJECT_NUM;
	cmd.config	= AUDPP_CMD_PCM_INTF_CONFIG_CMD_V;
	cmd.intf_type	= AUDPP_CMD_PCM_INTF_RX_ENA_ARMTODSP_V;

	if (yes) {
		cmd.write_buf1LSW	= audio->out[0].addr;
		cmd.write_buf1MSW	= audio->out[0].addr >> 16;
		cmd.write_buf1_len	= audio->out[0].size;
		cmd.write_buf2LSW	= audio->out[1].addr;
		cmd.write_buf2MSW	= audio->out[1].addr >> 16;
		cmd.write_buf2_len	= audio->out[1].size;
		cmd.arm_to_rx_flag	= AUDPP_CMD_PCM_INTF_ENA_V;
		cmd.weight_decoder_to_rx = audio->out_weight;
		cmd.weight_arm_to_rx	= 1;
		cmd.partition_number_arm_to_dsp = 0;
		cmd.sample_rate		= audio->out_sample_rate;
		cmd.channel_mode	= audio->out_channel_mode;
	}

	return audpp_send_queue2(&cmd, sizeof(cmd));
}