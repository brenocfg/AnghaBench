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
struct audplay_cmd_buffer_refresh {int num_buffers; int /*<<< orphan*/  buf0_length; int /*<<< orphan*/  buf0_address; scalar_t__ buf_read_count; int /*<<< orphan*/  cmd_id; } ;
struct audio {size_t fill_next; TYPE_1__* in; } ;
typedef  int /*<<< orphan*/  refresh_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPLAY_CMD_BUFFER_REFRESH ; 
 int /*<<< orphan*/  audplay_send_queue0 (struct audio*,struct audplay_cmd_buffer_refresh*,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void audqcelp_buffer_refresh(struct audio *audio)
{
	struct audplay_cmd_buffer_refresh refresh_cmd;

	refresh_cmd.cmd_id = AUDPLAY_CMD_BUFFER_REFRESH;
	refresh_cmd.num_buffers = 1;
	refresh_cmd.buf0_address = audio->in[audio->fill_next].addr;
	refresh_cmd.buf0_length = audio->in[audio->fill_next].size;
	refresh_cmd.buf_read_count = 0;
	dprintk("audplay_buffer_fresh: buf0_addr=%x buf0_len=%d\n",
		refresh_cmd.buf0_address, refresh_cmd.buf0_length);

	(void)audplay_send_queue0(audio, &refresh_cmd, sizeof(refresh_cmd));
}