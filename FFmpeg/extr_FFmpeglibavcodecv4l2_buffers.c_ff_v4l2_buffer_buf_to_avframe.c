#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct TYPE_33__ {TYPE_5__ output; } ;
typedef  TYPE_8__ V4L2m2mContext ;
struct TYPE_31__ {int flags; } ;
struct TYPE_34__ {int num_planes; TYPE_7__* context; TYPE_6__ buf; TYPE_1__* plane_info; } ;
typedef  TYPE_9__ V4L2Buffer ;
struct TYPE_27__ {int height; } ;
struct TYPE_28__ {TYPE_2__ pix_mp; } ;
struct TYPE_29__ {TYPE_3__ fmt; } ;
struct TYPE_32__ {int av_pix_fmt; int /*<<< orphan*/  name; TYPE_4__ format; } ;
struct TYPE_26__ {int bytesperline; } ;
struct TYPE_25__ {int data; } ;
struct TYPE_24__ {int* linesize; int* data; int key_frame; int format; int /*<<< orphan*/  decode_error_flags; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  pts; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_range; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  color_primaries; TYPE_17__** buf; } ;
typedef  TYPE_10__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PIX_FMT_NV12 128 
 int /*<<< orphan*/  FF_DECODE_ERROR_INVALID_BITSTREAM ; 
 int V4L2_BUF_FLAG_ERROR ; 
 int V4L2_BUF_FLAG_KEYFRAME ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_10__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_8__* buf_to_m2mctx (TYPE_9__*) ; 
 int /*<<< orphan*/  logger (TYPE_9__*) ; 
 int v4l2_buf_to_bufref (TYPE_9__*,int,TYPE_17__**) ; 
 int /*<<< orphan*/  v4l2_get_color_primaries (TYPE_9__*) ; 
 int /*<<< orphan*/  v4l2_get_color_range (TYPE_9__*) ; 
 int /*<<< orphan*/  v4l2_get_color_space (TYPE_9__*) ; 
 int /*<<< orphan*/  v4l2_get_color_trc (TYPE_9__*) ; 
 int /*<<< orphan*/  v4l2_get_pts (TYPE_9__*) ; 

int ff_v4l2_buffer_buf_to_avframe(AVFrame *frame, V4L2Buffer *avbuf)
{
    V4L2m2mContext *s = buf_to_m2mctx(avbuf);
    int i, ret;

    av_frame_unref(frame);

    /* 1. get references to the actual data */
    for (i = 0; i < avbuf->num_planes; i++) {
        ret = v4l2_buf_to_bufref(avbuf, i, &frame->buf[i]);
        if (ret)
            return ret;

        frame->linesize[i] = avbuf->plane_info[i].bytesperline;
        frame->data[i] = frame->buf[i]->data;
    }

    /* 1.1 fixup special cases */
    switch (avbuf->context->av_pix_fmt) {
    case AV_PIX_FMT_NV12:
        if (avbuf->num_planes > 1)
            break;
        frame->linesize[1] = avbuf->plane_info[0].bytesperline;
        frame->data[1] = frame->buf[0]->data + avbuf->plane_info[0].bytesperline * avbuf->context->format.fmt.pix_mp.height;
        break;
    default:
        break;
    }

    /* 2. get frame information */
    frame->key_frame = !!(avbuf->buf.flags & V4L2_BUF_FLAG_KEYFRAME);
    frame->format = avbuf->context->av_pix_fmt;
    frame->color_primaries = v4l2_get_color_primaries(avbuf);
    frame->colorspace = v4l2_get_color_space(avbuf);
    frame->color_range = v4l2_get_color_range(avbuf);
    frame->color_trc = v4l2_get_color_trc(avbuf);
    frame->pts = v4l2_get_pts(avbuf);

    /* these two values are updated also during re-init in v4l2_process_driver_event */
    frame->height = s->output.height;
    frame->width = s->output.width;

    /* 3. report errors upstream */
    if (avbuf->buf.flags & V4L2_BUF_FLAG_ERROR) {
        av_log(logger(avbuf), AV_LOG_ERROR, "%s: driver decode error\n", avbuf->context->name);
        frame->decode_error_flags |= FF_DECODE_ERROR_INVALID_BITSTREAM;
    }

    return 0;
}