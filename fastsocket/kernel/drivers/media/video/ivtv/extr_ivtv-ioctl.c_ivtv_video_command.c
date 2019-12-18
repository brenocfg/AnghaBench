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
struct TYPE_4__ {int /*<<< orphan*/  pts; } ;
struct TYPE_3__ {int speed; int /*<<< orphan*/  format; } ;
struct video_command {int cmd; int flags; TYPE_2__ stop; TYPE_1__ play; } ;
struct ivtv_stream {int dummy; } ;
struct ivtv_open_id {int dummy; } ;
struct ivtv {int v4l2_cap; int speed; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  output_mode; int /*<<< orphan*/  decoding; struct ivtv_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_DEC_PAUSE_PLAYBACK ; 
 int EBUSY ; 
 int EINVAL ; 
 size_t IVTV_DEC_STREAM_TYPE_MPG ; 
 int /*<<< orphan*/  IVTV_F_I_DEC_PAUSED ; 
 int /*<<< orphan*/  OUT_MPG ; 
 int /*<<< orphan*/  OUT_NONE ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
#define  VIDEO_CMD_CONTINUE 131 
#define  VIDEO_CMD_FREEZE 130 
 int VIDEO_CMD_FREEZE_TO_BLACK ; 
#define  VIDEO_CMD_PLAY 129 
#define  VIDEO_CMD_STOP 128 
 int VIDEO_CMD_STOP_IMMEDIATELY ; 
 int VIDEO_CMD_STOP_TO_BLACK ; 
 int /*<<< orphan*/  VIDEO_PLAY_FMT_GOP ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_set_output_mode (struct ivtv*,int /*<<< orphan*/ ) ; 
 int ivtv_start_decoding (struct ivtv_open_id*,int) ; 
 int ivtv_stop_v4l2_decode_stream (struct ivtv_stream*,int,int /*<<< orphan*/ ) ; 
 int ivtv_validate_speed (int,int) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ivtv_video_command(struct ivtv *itv, struct ivtv_open_id *id,
		struct video_command *vc, int try)
{
	struct ivtv_stream *s = &itv->streams[IVTV_DEC_STREAM_TYPE_MPG];

	if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		return -EINVAL;

	switch (vc->cmd) {
	case VIDEO_CMD_PLAY: {
		vc->flags = 0;
		vc->play.speed = ivtv_validate_speed(itv->speed, vc->play.speed);
		if (vc->play.speed < 0)
			vc->play.format = VIDEO_PLAY_FMT_GOP;
		if (try) break;

		if (ivtv_set_output_mode(itv, OUT_MPG) != OUT_MPG)
			return -EBUSY;
		if (test_and_clear_bit(IVTV_F_I_DEC_PAUSED, &itv->i_flags)) {
			/* forces ivtv_set_speed to be called */
			itv->speed = 0;
		}
		return ivtv_start_decoding(id, vc->play.speed);
	}

	case VIDEO_CMD_STOP:
		vc->flags &= VIDEO_CMD_STOP_IMMEDIATELY|VIDEO_CMD_STOP_TO_BLACK;
		if (vc->flags & VIDEO_CMD_STOP_IMMEDIATELY)
			vc->stop.pts = 0;
		if (try) break;
		if (atomic_read(&itv->decoding) == 0)
			return 0;
		if (itv->output_mode != OUT_MPG)
			return -EBUSY;

		itv->output_mode = OUT_NONE;
		return ivtv_stop_v4l2_decode_stream(s, vc->flags, vc->stop.pts);

	case VIDEO_CMD_FREEZE:
		vc->flags &= VIDEO_CMD_FREEZE_TO_BLACK;
		if (try) break;
		if (itv->output_mode != OUT_MPG)
			return -EBUSY;
		if (atomic_read(&itv->decoding) > 0) {
			ivtv_vapi(itv, CX2341X_DEC_PAUSE_PLAYBACK, 1,
				(vc->flags & VIDEO_CMD_FREEZE_TO_BLACK) ? 1 : 0);
			set_bit(IVTV_F_I_DEC_PAUSED, &itv->i_flags);
		}
		break;

	case VIDEO_CMD_CONTINUE:
		vc->flags = 0;
		if (try) break;
		if (itv->output_mode != OUT_MPG)
			return -EBUSY;
		if (test_and_clear_bit(IVTV_F_I_DEC_PAUSED, &itv->i_flags)) {
			int speed = itv->speed;
			itv->speed = 0;
			return ivtv_start_decoding(id, speed);
		}
		break;

	default:
		return -EINVAL;
	}
	return 0;
}