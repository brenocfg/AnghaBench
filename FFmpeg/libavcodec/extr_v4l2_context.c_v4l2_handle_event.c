#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct v4l2_format {scalar_t__ type; int /*<<< orphan*/  member_0; } ;
struct v4l2_event {scalar_t__ type; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {void* height; void* width; void* sample_aspect_ratio; int /*<<< orphan*/  name; struct v4l2_format format; } ;
struct TYPE_11__ {int reinit; TYPE_3__ capture; scalar_t__ avctx; TYPE_3__ output; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ V4L2m2mContext ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ V4L2Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int EINVAL ; 
 scalar_t__ V4L2_EVENT_SOURCE_CHANGE ; 
 int /*<<< orphan*/  VIDIOC_DQEVENT ; 
 int /*<<< orphan*/  VIDIOC_G_FMT ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* ctx_to_m2mctx (TYPE_2__*) ; 
 int ff_set_dimensions (scalar_t__,void*,void*) ; 
 int ff_v4l2_m2m_codec_full_reinit (TYPE_1__*) ; 
 int ff_v4l2_m2m_codec_reinit (TYPE_1__*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_format*) ; 
 int /*<<< orphan*/  logger (TYPE_2__*) ; 
 void* v4l2_get_height (struct v4l2_format*) ; 
 void* v4l2_get_sar (TYPE_3__*) ; 
 void* v4l2_get_width (struct v4l2_format*) ; 
 int v4l2_resolution_changed (TYPE_3__*,struct v4l2_format*) ; 

__attribute__((used)) static int v4l2_handle_event(V4L2Context *ctx)
{
    V4L2m2mContext *s = ctx_to_m2mctx(ctx);
    struct v4l2_format cap_fmt = s->capture.format;
    struct v4l2_format out_fmt = s->output.format;
    struct v4l2_event evt = { 0 };
    int full_reinit, reinit, ret;

    ret = ioctl(s->fd, VIDIOC_DQEVENT, &evt);
    if (ret < 0) {
        av_log(logger(ctx), AV_LOG_ERROR, "%s VIDIOC_DQEVENT\n", ctx->name);
        return 0;
    }

    if (evt.type != V4L2_EVENT_SOURCE_CHANGE)
        return 0;

    ret = ioctl(s->fd, VIDIOC_G_FMT, &out_fmt);
    if (ret) {
        av_log(logger(ctx), AV_LOG_ERROR, "%s VIDIOC_G_FMT\n", s->output.name);
        return 0;
    }

    ret = ioctl(s->fd, VIDIOC_G_FMT, &cap_fmt);
    if (ret) {
        av_log(logger(ctx), AV_LOG_ERROR, "%s VIDIOC_G_FMT\n", s->capture.name);
        return 0;
    }

    full_reinit = v4l2_resolution_changed(&s->output, &out_fmt);
    if (full_reinit) {
        s->output.height = v4l2_get_height(&out_fmt);
        s->output.width = v4l2_get_width(&out_fmt);
        s->output.sample_aspect_ratio = v4l2_get_sar(&s->output);
    }

    reinit = v4l2_resolution_changed(&s->capture, &cap_fmt);
    if (reinit) {
        s->capture.height = v4l2_get_height(&cap_fmt);
        s->capture.width = v4l2_get_width(&cap_fmt);
        s->capture.sample_aspect_ratio = v4l2_get_sar(&s->capture);
    }

    if (full_reinit || reinit)
        s->reinit = 1;

    if (full_reinit) {
        ret = ff_v4l2_m2m_codec_full_reinit(s);
        if (ret) {
            av_log(logger(ctx), AV_LOG_ERROR, "v4l2_m2m_codec_full_reinit\n");
            return -EINVAL;
        }
        goto reinit_run;
    }

    if (reinit) {
        if (s->avctx)
            ret = ff_set_dimensions(s->avctx, s->capture.width, s->capture.height);
        if (ret < 0)
            av_log(logger(ctx), AV_LOG_WARNING, "update avcodec height and width\n");

        ret = ff_v4l2_m2m_codec_reinit(s);
        if (ret) {
            av_log(logger(ctx), AV_LOG_ERROR, "v4l2_m2m_codec_reinit\n");
            return -EINVAL;
        }
        goto reinit_run;
    }

    /* dummy event received */
    return 0;

    /* reinit executed */
reinit_run:
    return 1;
}