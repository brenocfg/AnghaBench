#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct TYPE_5__ {int width; int height; scalar_t__ top; scalar_t__ left; } ;
struct yuv_playback_info {int osd_full_w; int osd_full_h; TYPE_2__ main_rect; } ;
struct ivtv_open_id {struct ivtv* itv; } ;
struct TYPE_6__ {int width; int height; } ;
struct TYPE_4__ {int count; int* start; int sliced_decoder_line_size; } ;
struct ivtv {int std; int is_60hz; int is_50hz; int hw_flags; int v4l2_cap; int std_out; int is_out_60hz; int is_out_50hz; int /*<<< orphan*/  osd_info; TYPE_2__ main_rect; TYPE_3__ cxhdl; int /*<<< orphan*/  vsync_waitq; TYPE_1__ vbi; int /*<<< orphan*/  decoding; int /*<<< orphan*/  capturing; int /*<<< orphan*/  i_flags; struct yuv_playback_info yuv_info; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_DEC_SET_STANDARD ; 
 int /*<<< orphan*/  CX2341X_OSD_SET_FRAMEBUFFER_WINDOW ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,unsigned long long) ; 
 int /*<<< orphan*/  IVTV_F_I_RADIO_USER ; 
 int IVTV_HW_CX25840 ; 
 int /*<<< orphan*/  IVTV_REG_DEC_LINE_FIELD ; 
 int /*<<< orphan*/  IVTV_WARN (char*) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_ALL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  cx2341x_handler_set_50hz (TYPE_3__*,int) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_call_all (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  s_std_output ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  wait ; 

int ivtv_s_std(struct file *file, void *fh, v4l2_std_id *std)
{
	DEFINE_WAIT(wait);
	struct ivtv *itv = ((struct ivtv_open_id *)fh)->itv;
	struct yuv_playback_info *yi = &itv->yuv_info;
	int f;

	if ((*std & V4L2_STD_ALL) == 0)
		return -EINVAL;

	if (*std == itv->std)
		return 0;

	if (test_bit(IVTV_F_I_RADIO_USER, &itv->i_flags) ||
	    atomic_read(&itv->capturing) > 0 ||
	    atomic_read(&itv->decoding) > 0) {
		/* Switching standard would turn off the radio or mess
		   with already running streams, prevent that by
		   returning EBUSY. */
		return -EBUSY;
	}

	itv->std = *std;
	itv->is_60hz = (*std & V4L2_STD_525_60) ? 1 : 0;
	itv->is_50hz = !itv->is_60hz;
	cx2341x_handler_set_50hz(&itv->cxhdl, itv->is_50hz);
	itv->cxhdl.width = 720;
	itv->cxhdl.height = itv->is_50hz ? 576 : 480;
	itv->vbi.count = itv->is_50hz ? 18 : 12;
	itv->vbi.start[0] = itv->is_50hz ? 6 : 10;
	itv->vbi.start[1] = itv->is_50hz ? 318 : 273;

	if (itv->hw_flags & IVTV_HW_CX25840)
		itv->vbi.sliced_decoder_line_size = itv->is_60hz ? 272 : 284;

	IVTV_DEBUG_INFO("Switching standard to %llx.\n", (unsigned long long)itv->std);

	/* Tuner */
	ivtv_call_all(itv, core, s_std, itv->std);

	if (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT) {
		/* set display standard */
		itv->std_out = *std;
		itv->is_out_60hz = itv->is_60hz;
		itv->is_out_50hz = itv->is_50hz;
		ivtv_call_all(itv, video, s_std_output, itv->std_out);

		/*
		 * The next firmware call is time sensitive. Time it to
		 * avoid risk of a hard lock, by trying to ensure the call
		 * happens within the first 100 lines of the top field.
		 * Make 4 attempts to sync to the decoder before giving up.
		 */
		for (f = 0; f < 4; f++) {
			prepare_to_wait(&itv->vsync_waitq, &wait,
					TASK_UNINTERRUPTIBLE);
			if ((read_reg(IVTV_REG_DEC_LINE_FIELD) >> 16) < 100)
				break;
			schedule_timeout(msecs_to_jiffies(25));
		}
		finish_wait(&itv->vsync_waitq, &wait);

		if (f == 4)
			IVTV_WARN("Mode change failed to sync to decoder\n");

		ivtv_vapi(itv, CX2341X_DEC_SET_STANDARD, 1, itv->is_out_50hz);
		itv->main_rect.left = itv->main_rect.top = 0;
		itv->main_rect.width = 720;
		itv->main_rect.height = itv->cxhdl.height;
		ivtv_vapi(itv, CX2341X_OSD_SET_FRAMEBUFFER_WINDOW, 4,
			720, itv->main_rect.height, 0, 0);
		yi->main_rect = itv->main_rect;
		if (!itv->osd_info) {
			yi->osd_full_w = 720;
			yi->osd_full_h = itv->is_out_50hz ? 576 : 480;
		}
	}
	return 0;
}