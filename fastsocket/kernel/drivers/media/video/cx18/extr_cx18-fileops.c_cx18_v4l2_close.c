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
struct file {struct cx18_open_id* private_data; } ;
struct cx18_stream {scalar_t__ id; int /*<<< orphan*/  handle; int /*<<< orphan*/  name; } ;
struct cx18_open_id {size_t type; scalar_t__ open_id; int /*<<< orphan*/  prio; struct cx18* cx; } ;
struct TYPE_2__ {int video_mute; int video_mute_yuv; } ;
struct cx18 {int /*<<< orphan*/  serialize_lock; TYPE_1__ params; int /*<<< orphan*/  ana_capturing; int /*<<< orphan*/  std; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  prio; struct cx18_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_CPU_SET_VIDEO_MUTE ; 
 int /*<<< orphan*/  CX18_DEBUG_IOCTL (char*,int /*<<< orphan*/ ) ; 
 size_t CX18_ENC_STREAM_TYPE_RAD ; 
 int /*<<< orphan*/  CX18_F_I_RADIO_USER ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  cx18_audio_set_io (struct cx18*) ; 
 int /*<<< orphan*/  cx18_call_all (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_mute (struct cx18*) ; 
 int /*<<< orphan*/  cx18_release_stream (struct cx18_stream*) ; 
 int /*<<< orphan*/  cx18_stop_capture (struct cx18_open_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_unmute (struct cx18*) ; 
 int /*<<< orphan*/  cx18_vapi (struct cx18*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct cx18_open_id*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  v4l2_prio_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cx18_v4l2_close(struct file *filp)
{
	struct cx18_open_id *id = filp->private_data;
	struct cx18 *cx = id->cx;
	struct cx18_stream *s = &cx->streams[id->type];

	CX18_DEBUG_IOCTL("close() of %s\n", s->name);

	v4l2_prio_close(&cx->prio, id->prio);

	/* Easy case first: this stream was never claimed by us */
	if (s->id != id->open_id) {
		kfree(id);
		return 0;
	}

	/* 'Unclaim' this stream */

	/* Stop radio */
	mutex_lock(&cx->serialize_lock);
	if (id->type == CX18_ENC_STREAM_TYPE_RAD) {
		/* Closing radio device, return to TV mode */
		cx18_mute(cx);
		/* Mark that the radio is no longer in use */
		clear_bit(CX18_F_I_RADIO_USER, &cx->i_flags);
		/* Switch tuner to TV */
		cx18_call_all(cx, core, s_std, cx->std);
		/* Select correct audio input (i.e. TV tuner or Line in) */
		cx18_audio_set_io(cx);
		if (atomic_read(&cx->ana_capturing) > 0) {
			/* Undo video mute */
			cx18_vapi(cx, CX18_CPU_SET_VIDEO_MUTE, 2, s->handle,
				cx->params.video_mute |
					(cx->params.video_mute_yuv << 8));
		}
		/* Done! Unmute and continue. */
		cx18_unmute(cx);
		cx18_release_stream(s);
	} else {
		cx18_stop_capture(id, 0);
	}
	kfree(id);
	mutex_unlock(&cx->serialize_lock);
	return 0;
}