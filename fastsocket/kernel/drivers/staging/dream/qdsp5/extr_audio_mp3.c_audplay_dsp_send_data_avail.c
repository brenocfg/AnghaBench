#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct audio {TYPE_1__* out; int /*<<< orphan*/  dec_id; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {unsigned int buf_size; scalar_t__ partition_number; int /*<<< orphan*/  buf_ptr; int /*<<< orphan*/  decoder_id; int /*<<< orphan*/  cmd_id; } ;
typedef  TYPE_2__ audplay_cmd_bitstream_data_avail ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPLAY_CMD_BITSTREAM_DATA_AVAIL ; 
 int audplay_send_queue0 (struct audio*,TYPE_2__*,int) ; 

__attribute__((used)) static int audplay_dsp_send_data_avail(struct audio *audio,
					unsigned idx, unsigned len)
{
	audplay_cmd_bitstream_data_avail cmd;

	cmd.cmd_id		= AUDPLAY_CMD_BITSTREAM_DATA_AVAIL;
	cmd.decoder_id		= audio->dec_id;
	cmd.buf_ptr		= audio->out[idx].addr;
	cmd.buf_size		= len/2;
	cmd.partition_number	= 0;
	return audplay_send_queue0(audio, &cmd, sizeof(cmd));
}