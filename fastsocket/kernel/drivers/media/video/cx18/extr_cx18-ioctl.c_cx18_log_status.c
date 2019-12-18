#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_input {char* name; } ;
struct v4l2_audio {char* name; } ;
struct tveeprom {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  depth; } ;
struct cx18_stream {int buffers; int bufs_per_mdl; int buf_size; TYPE_2__ q_full; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  name; int /*<<< orphan*/ * video_dev; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct cx18 {char* instance; int hw_flags; char* i_flags; scalar_t__ vbi_data_inserted; scalar_t__ mpg_data_received; struct cx18_stream* streams; TYPE_1__ v4l2_dev; int /*<<< orphan*/  params; int /*<<< orphan*/  gpio_lock; int /*<<< orphan*/  gpio_val; int /*<<< orphan*/  gpio_dir; int /*<<< orphan*/  audio_input; int /*<<< orphan*/  active_input; int /*<<< orphan*/  card_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_F_I_RADIO_USER ; 
 int CX18_HW_TVEEPROM ; 
 int /*<<< orphan*/  CX18_INFO (char*,...) ; 
 int CX18_MAX_STREAMS ; 
 int /*<<< orphan*/  CX18_VERSION ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  cx18_call_all (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_get_audio_input (struct cx18*,int /*<<< orphan*/ ,struct v4l2_audio*) ; 
 int /*<<< orphan*/  cx18_get_input (struct cx18*,int /*<<< orphan*/ ,struct v4l2_input*) ; 
 int /*<<< orphan*/  cx18_read_eeprom (struct cx18*,struct tveeprom*) ; 
 int /*<<< orphan*/  cx2341x_log_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_status ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int cx18_log_status(struct file *file, void *fh)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;
	struct v4l2_input vidin;
	struct v4l2_audio audin;
	int i;

	CX18_INFO("=================  START STATUS CARD #%d  "
		  "=================\n", cx->instance);
	CX18_INFO("Version: %s  Card: %s\n", CX18_VERSION, cx->card_name);
	if (cx->hw_flags & CX18_HW_TVEEPROM) {
		struct tveeprom tv;

		cx18_read_eeprom(cx, &tv);
	}
	cx18_call_all(cx, core, log_status);
	cx18_get_input(cx, cx->active_input, &vidin);
	cx18_get_audio_input(cx, cx->audio_input, &audin);
	CX18_INFO("Video Input: %s\n", vidin.name);
	CX18_INFO("Audio Input: %s\n", audin.name);
	mutex_lock(&cx->gpio_lock);
	CX18_INFO("GPIO:  direction 0x%08x, value 0x%08x\n",
		cx->gpio_dir, cx->gpio_val);
	mutex_unlock(&cx->gpio_lock);
	CX18_INFO("Tuner: %s\n",
		test_bit(CX18_F_I_RADIO_USER, &cx->i_flags) ?  "Radio" : "TV");
	cx2341x_log_status(&cx->params, cx->v4l2_dev.name);
	CX18_INFO("Status flags: 0x%08lx\n", cx->i_flags);
	for (i = 0; i < CX18_MAX_STREAMS; i++) {
		struct cx18_stream *s = &cx->streams[i];

		if (s->video_dev == NULL || s->buffers == 0)
			continue;
		CX18_INFO("Stream %s: status 0x%04lx, %d%% of %d KiB (%d buffers) in use\n",
			  s->name, s->s_flags,
			  atomic_read(&s->q_full.depth) * s->bufs_per_mdl * 100
			   / s->buffers,
			  (s->buffers * s->buf_size) / 1024, s->buffers);
	}
	CX18_INFO("Read MPEG/VBI: %lld/%lld bytes\n",
			(long long)cx->mpg_data_received,
			(long long)cx->vbi_data_inserted);
	CX18_INFO("==================  END STATUS CARD #%d  "
		  "==================\n", cx->instance);
	return 0;
}