#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int flags; } ;
struct TYPE_18__ {TYPE_2__* context; TYPE_1__ buf; } ;
typedef  TYPE_3__ V4L2Buffer ;
struct TYPE_19__ {int key_frame; int /*<<< orphan*/  decode_error_flags; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  pkt_dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_range; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  color_primaries; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
typedef  TYPE_4__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  FF_DECODE_ERROR_INVALID_BITSTREAM ; 
 int V4L2_BUF_FLAG_ERROR ; 
 int V4L2_BUF_FLAG_KEYFRAME ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logger (TYPE_3__*) ; 
 int v4l2_buffer_buf_to_swframe (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_get_color_primaries (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_get_color_range (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_get_color_space (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_get_color_trc (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_get_pts (TYPE_3__*) ; 

int ff_v4l2_buffer_buf_to_avframe(AVFrame *frame, V4L2Buffer *avbuf)
{
    int ret;

    av_frame_unref(frame);

    /* 1. get references to the actual data */
    ret = v4l2_buffer_buf_to_swframe(frame, avbuf);
    if (ret)
        return ret;

    /* 2. get frame information */
    frame->key_frame = !!(avbuf->buf.flags & V4L2_BUF_FLAG_KEYFRAME);
    frame->color_primaries = v4l2_get_color_primaries(avbuf);
    frame->colorspace = v4l2_get_color_space(avbuf);
    frame->color_range = v4l2_get_color_range(avbuf);
    frame->color_trc = v4l2_get_color_trc(avbuf);
    frame->pts = v4l2_get_pts(avbuf);
    frame->pkt_dts = AV_NOPTS_VALUE;

    /* these values are updated also during re-init in v4l2_process_driver_event */
    frame->height = avbuf->context->height;
    frame->width = avbuf->context->width;
    frame->sample_aspect_ratio = avbuf->context->sample_aspect_ratio;

    /* 3. report errors upstream */
    if (avbuf->buf.flags & V4L2_BUF_FLAG_ERROR) {
        av_log(logger(avbuf), AV_LOG_ERROR, "%s: driver decode error\n", avbuf->context->name);
        frame->decode_error_flags |= FF_DECODE_ERROR_INVALID_BITSTREAM;
    }

    return 0;
}