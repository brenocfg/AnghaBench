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
typedef  int /*<<< orphan*/  vc ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  vsync_field; } ;
struct video_event {int flags; int /*<<< orphan*/  type; TYPE_2__ u; int /*<<< orphan*/  cmd; } ;
struct video_command {int flags; int /*<<< orphan*/  type; TYPE_2__ u; int /*<<< orphan*/  cmd; } ;
struct ivtv_stream {int dma_pts; int /*<<< orphan*/  type; } ;
struct ivtv_open_id {size_t type; int yuv_frames; struct ivtv* itv; } ;
struct ivtv_dma_frame {int /*<<< orphan*/ * y_source; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int lace_mode; } ;
struct ivtv {int v4l2_cap; int* last_dec_timing; unsigned long speed_mute_audio; unsigned long audio_stereo_mode; unsigned long audio_bilingual_mode; int /*<<< orphan*/  serialize_lock; int /*<<< orphan*/  event_waitq; int /*<<< orphan*/  i_flags; TYPE_1__ yuv_info; int /*<<< orphan*/  output_mode; int /*<<< orphan*/  decoding; struct ivtv_stream* streams; } ;
struct file {int f_flags; int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
#define  AUDIO_BILINGUAL_CHANNEL_SELECT 141 
#define  AUDIO_CHANNEL_SELECT 140 
#define  AUDIO_SET_MUTE 139 
 unsigned long AUDIO_STEREO_SWAPPED ; 
 int /*<<< orphan*/  CX2341X_DEC_GET_TIMING_INFO ; 
 int /*<<< orphan*/  CX2341X_DEC_SET_AUDIO_MODE ; 
 int CX2341X_MBOX_MAX_DATA ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IVTV_DEBUG_IOCTL (char*,...) ; 
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*) ; 
 int /*<<< orphan*/  IVTV_DEC_STREAM_TYPE_MPG ; 
 int /*<<< orphan*/  IVTV_F_I_EV_DEC_STOPPED ; 
 int /*<<< orphan*/  IVTV_F_I_EV_VSYNC ; 
 int /*<<< orphan*/  IVTV_F_I_EV_VSYNC_ENABLED ; 
 int /*<<< orphan*/  IVTV_F_I_EV_VSYNC_FIELD ; 
 int /*<<< orphan*/  IVTV_F_I_VALID_DEC_TIMINGS ; 
#define  IVTV_IOC_DMA_FRAME 138 
 int IVTV_YUV_MODE_MASK ; 
 int IVTV_YUV_MODE_PROGRESSIVE ; 
 int /*<<< orphan*/  OUT_UDMA_YUV ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  VIDEO_CMD_CONTINUE ; 
 int /*<<< orphan*/  VIDEO_CMD_FREEZE ; 
 int /*<<< orphan*/  VIDEO_CMD_PLAY ; 
 int /*<<< orphan*/  VIDEO_CMD_STOP ; 
 int VIDEO_CMD_STOP_IMMEDIATELY ; 
 int VIDEO_CMD_STOP_TO_BLACK ; 
#define  VIDEO_COMMAND 137 
#define  VIDEO_CONTINUE 136 
 int /*<<< orphan*/  VIDEO_EVENT_DECODER_STOPPED ; 
 int /*<<< orphan*/  VIDEO_EVENT_VSYNC ; 
#define  VIDEO_FREEZE 135 
#define  VIDEO_GET_EVENT 134 
#define  VIDEO_GET_FRAME_COUNT 133 
#define  VIDEO_GET_PTS 132 
#define  VIDEO_PLAY 131 
#define  VIDEO_SELECT_SOURCE 130 
 unsigned long VIDEO_SOURCE_DEMUX ; 
#define  VIDEO_STOP 129 
#define  VIDEO_TRY_COMMAND 128 
 int /*<<< orphan*/  VIDEO_VSYNC_FIELD_EVEN ; 
 int /*<<< orphan*/  VIDEO_VSYNC_FIELD_ODD ; 
 int /*<<< orphan*/  VIDEO_VSYNC_FIELD_PROGRESSIVE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 struct ivtv_open_id* fh2id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_api (struct ivtv*,int /*<<< orphan*/ ,int,int*) ; 
 int ivtv_passthrough_mode (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_release_stream (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_set_output_mode (struct ivtv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_start_decoding (struct ivtv_open_id*,size_t) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,unsigned long,unsigned long) ; 
 int ivtv_video_command (struct ivtv*,struct ivtv_open_id*,struct video_event*,int) ; 
 int ivtv_yuv_prep_frame (struct ivtv*,struct ivtv_dma_frame*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (struct video_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int ivtv_decoder_ioctls(struct file *filp, unsigned int cmd, void *arg)
{
	struct ivtv_open_id *id = fh2id(filp->private_data);
	struct ivtv *itv = id->itv;
	int nonblocking = filp->f_flags & O_NONBLOCK;
	struct ivtv_stream *s = &itv->streams[id->type];
	unsigned long iarg = (unsigned long)arg;

	switch (cmd) {
	case IVTV_IOC_DMA_FRAME: {
		struct ivtv_dma_frame *args = arg;

		IVTV_DEBUG_IOCTL("IVTV_IOC_DMA_FRAME\n");
		if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			return -EINVAL;
		if (args->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			return -EINVAL;
		if (itv->output_mode == OUT_UDMA_YUV && args->y_source == NULL)
			return 0;
		if (ivtv_start_decoding(id, id->type)) {
			return -EBUSY;
		}
		if (ivtv_set_output_mode(itv, OUT_UDMA_YUV) != OUT_UDMA_YUV) {
			ivtv_release_stream(s);
			return -EBUSY;
		}
		/* Mark that this file handle started the UDMA_YUV mode */
		id->yuv_frames = 1;
		if (args->y_source == NULL)
			return 0;
		return ivtv_yuv_prep_frame(itv, args);
	}

	case VIDEO_GET_PTS: {
		u32 data[CX2341X_MBOX_MAX_DATA];
		u64 *pts = arg;

		IVTV_DEBUG_IOCTL("VIDEO_GET_PTS\n");
		if (s->type < IVTV_DEC_STREAM_TYPE_MPG) {
			*pts = s->dma_pts;
			break;
		}
		if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			return -EINVAL;

		if (test_bit(IVTV_F_I_VALID_DEC_TIMINGS, &itv->i_flags)) {
			*pts = (u64) ((u64)itv->last_dec_timing[2] << 32) |
					(u64)itv->last_dec_timing[1];
			break;
		}
		*pts = 0;
		if (atomic_read(&itv->decoding)) {
			if (ivtv_api(itv, CX2341X_DEC_GET_TIMING_INFO, 5, data)) {
				IVTV_DEBUG_WARN("GET_TIMING: couldn't read clock\n");
				return -EIO;
			}
			memcpy(itv->last_dec_timing, data, sizeof(itv->last_dec_timing));
			set_bit(IVTV_F_I_VALID_DEC_TIMINGS, &itv->i_flags);
			*pts = (u64) ((u64) data[2] << 32) | (u64) data[1];
			/*timing->scr = (u64) (((u64) data[4] << 32) | (u64) (data[3]));*/
		}
		break;
	}

	case VIDEO_GET_FRAME_COUNT: {
		u32 data[CX2341X_MBOX_MAX_DATA];
		u64 *frame = arg;

		IVTV_DEBUG_IOCTL("VIDEO_GET_FRAME_COUNT\n");
		if (s->type < IVTV_DEC_STREAM_TYPE_MPG) {
			*frame = 0;
			break;
		}
		if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			return -EINVAL;

		if (test_bit(IVTV_F_I_VALID_DEC_TIMINGS, &itv->i_flags)) {
			*frame = itv->last_dec_timing[0];
			break;
		}
		*frame = 0;
		if (atomic_read(&itv->decoding)) {
			if (ivtv_api(itv, CX2341X_DEC_GET_TIMING_INFO, 5, data)) {
				IVTV_DEBUG_WARN("GET_TIMING: couldn't read clock\n");
				return -EIO;
			}
			memcpy(itv->last_dec_timing, data, sizeof(itv->last_dec_timing));
			set_bit(IVTV_F_I_VALID_DEC_TIMINGS, &itv->i_flags);
			*frame = data[0];
		}
		break;
	}

	case VIDEO_PLAY: {
		struct video_command vc;

		IVTV_DEBUG_IOCTL("VIDEO_PLAY\n");
		memset(&vc, 0, sizeof(vc));
		vc.cmd = VIDEO_CMD_PLAY;
		return ivtv_video_command(itv, id, &vc, 0);
	}

	case VIDEO_STOP: {
		struct video_command vc;

		IVTV_DEBUG_IOCTL("VIDEO_STOP\n");
		memset(&vc, 0, sizeof(vc));
		vc.cmd = VIDEO_CMD_STOP;
		vc.flags = VIDEO_CMD_STOP_TO_BLACK | VIDEO_CMD_STOP_IMMEDIATELY;
		return ivtv_video_command(itv, id, &vc, 0);
	}

	case VIDEO_FREEZE: {
		struct video_command vc;

		IVTV_DEBUG_IOCTL("VIDEO_FREEZE\n");
		memset(&vc, 0, sizeof(vc));
		vc.cmd = VIDEO_CMD_FREEZE;
		return ivtv_video_command(itv, id, &vc, 0);
	}

	case VIDEO_CONTINUE: {
		struct video_command vc;

		IVTV_DEBUG_IOCTL("VIDEO_CONTINUE\n");
		memset(&vc, 0, sizeof(vc));
		vc.cmd = VIDEO_CMD_CONTINUE;
		return ivtv_video_command(itv, id, &vc, 0);
	}

	case VIDEO_COMMAND:
	case VIDEO_TRY_COMMAND: {
		struct video_command *vc = arg;
		int try = (cmd == VIDEO_TRY_COMMAND);

		if (try)
			IVTV_DEBUG_IOCTL("VIDEO_TRY_COMMAND %d\n", vc->cmd);
		else
			IVTV_DEBUG_IOCTL("VIDEO_COMMAND %d\n", vc->cmd);
		return ivtv_video_command(itv, id, vc, try);
	}

	case VIDEO_GET_EVENT: {
		struct video_event *ev = arg;
		DEFINE_WAIT(wait);

		IVTV_DEBUG_IOCTL("VIDEO_GET_EVENT\n");
		if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			return -EINVAL;
		memset(ev, 0, sizeof(*ev));
		set_bit(IVTV_F_I_EV_VSYNC_ENABLED, &itv->i_flags);

		while (1) {
			if (test_and_clear_bit(IVTV_F_I_EV_DEC_STOPPED, &itv->i_flags))
				ev->type = VIDEO_EVENT_DECODER_STOPPED;
			else if (test_and_clear_bit(IVTV_F_I_EV_VSYNC, &itv->i_flags)) {
				ev->type = VIDEO_EVENT_VSYNC;
				ev->u.vsync_field = test_bit(IVTV_F_I_EV_VSYNC_FIELD, &itv->i_flags) ?
					VIDEO_VSYNC_FIELD_ODD : VIDEO_VSYNC_FIELD_EVEN;
				if (itv->output_mode == OUT_UDMA_YUV &&
					(itv->yuv_info.lace_mode & IVTV_YUV_MODE_MASK) ==
								IVTV_YUV_MODE_PROGRESSIVE) {
					ev->u.vsync_field = VIDEO_VSYNC_FIELD_PROGRESSIVE;
				}
			}
			if (ev->type)
				return 0;
			if (nonblocking)
				return -EAGAIN;
			/* Wait for event. Note that serialize_lock is locked,
			   so to allow other processes to access the driver while
			   we are waiting unlock first and later lock again. */
			mutex_unlock(&itv->serialize_lock);
			prepare_to_wait(&itv->event_waitq, &wait, TASK_INTERRUPTIBLE);
			if (!test_bit(IVTV_F_I_EV_DEC_STOPPED, &itv->i_flags) &&
			    !test_bit(IVTV_F_I_EV_VSYNC, &itv->i_flags))
				schedule();
			finish_wait(&itv->event_waitq, &wait);
			mutex_lock(&itv->serialize_lock);
			if (signal_pending(current)) {
				/* return if a signal was received */
				IVTV_DEBUG_INFO("User stopped wait for event\n");
				return -EINTR;
			}
		}
		break;
	}

	case VIDEO_SELECT_SOURCE:
		IVTV_DEBUG_IOCTL("VIDEO_SELECT_SOURCE\n");
		if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			return -EINVAL;
		return ivtv_passthrough_mode(itv, iarg == VIDEO_SOURCE_DEMUX);

	case AUDIO_SET_MUTE:
		IVTV_DEBUG_IOCTL("AUDIO_SET_MUTE\n");
		itv->speed_mute_audio = iarg;
		return 0;

	case AUDIO_CHANNEL_SELECT:
		IVTV_DEBUG_IOCTL("AUDIO_CHANNEL_SELECT\n");
		if (iarg > AUDIO_STEREO_SWAPPED)
			return -EINVAL;
		itv->audio_stereo_mode = iarg;
		ivtv_vapi(itv, CX2341X_DEC_SET_AUDIO_MODE, 2, itv->audio_bilingual_mode, itv->audio_stereo_mode);
		return 0;

	case AUDIO_BILINGUAL_CHANNEL_SELECT:
		IVTV_DEBUG_IOCTL("AUDIO_BILINGUAL_CHANNEL_SELECT\n");
		if (iarg > AUDIO_STEREO_SWAPPED)
			return -EINVAL;
		itv->audio_bilingual_mode = iarg;
		ivtv_vapi(itv, CX2341X_DEC_SET_AUDIO_MODE, 2, itv->audio_bilingual_mode, itv->audio_stereo_mode);
		return 0;

	default:
		return -EINVAL;
	}
	return 0;
}