#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct audio_in {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int curr_rec_count_msw; int curr_rec_count_lsw; int /*<<< orphan*/  type; int /*<<< orphan*/  cmd_id; } ;
typedef  TYPE_1__ audrec_cmd_packet_ext_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  AUDREC_CMD_PACKET_EXT_PTR ; 
 int /*<<< orphan*/  AUDREC_CMD_TYPE_0 ; 
 int audio_send_queue_recbs (struct audio_in*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int audio_dsp_read_buffer(struct audio_in *audio, uint32_t read_cnt)
{
	audrec_cmd_packet_ext_ptr cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd_id = AUDREC_CMD_PACKET_EXT_PTR;
	/* Both WAV and AAC use AUDREC_CMD_TYPE_0 */
	cmd.type = AUDREC_CMD_TYPE_0;
	cmd.curr_rec_count_msw = read_cnt >> 16;
	cmd.curr_rec_count_lsw = read_cnt;

	return audio_send_queue_recbs(audio, &cmd, sizeof(cmd));
}