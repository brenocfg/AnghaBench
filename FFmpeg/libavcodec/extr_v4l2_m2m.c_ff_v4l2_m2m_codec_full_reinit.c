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
struct TYPE_5__ {int /*<<< orphan*/  capture; TYPE_1__* avctx; int /*<<< orphan*/  output; scalar_t__ reinit; scalar_t__ draining; int /*<<< orphan*/  refsync; int /*<<< orphan*/  refcount; int /*<<< orphan*/  devname; } ;
typedef  TYPE_2__ V4L2m2mContext ;
struct TYPE_4__ {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  VIDIOC_STREAMOFF ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_codec_is_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ errno ; 
 int ff_v4l2_context_get_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_v4l2_context_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_v4l2_context_release (int /*<<< orphan*/ *) ; 
 int ff_v4l2_context_set_format (int /*<<< orphan*/ *) ; 
 int ff_v4l2_context_set_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sem_wait (int /*<<< orphan*/ *) ; 

int ff_v4l2_m2m_codec_full_reinit(V4L2m2mContext *s)
{
    void *log_ctx = s->avctx;
    int ret;

    av_log(log_ctx, AV_LOG_DEBUG, "%s full reinit\n", s->devname);

    /* wait for pending buffer references */
    if (atomic_load(&s->refcount))
        while(sem_wait(&s->refsync) == -1 && errno == EINTR);

    ret = ff_v4l2_context_set_status(&s->output, VIDIOC_STREAMOFF);
    if (ret) {
        av_log(log_ctx, AV_LOG_ERROR, "output VIDIOC_STREAMOFF\n");
        goto error;
    }

    ret = ff_v4l2_context_set_status(&s->capture, VIDIOC_STREAMOFF);
    if (ret) {
            av_log(log_ctx, AV_LOG_ERROR, "capture VIDIOC_STREAMOFF\n");
            goto error;
    }

    /* release and unmmap the buffers */
    ff_v4l2_context_release(&s->output);
    ff_v4l2_context_release(&s->capture);

    /* start again now that we know the stream dimensions */
    s->draining = 0;
    s->reinit = 0;

    ret = ff_v4l2_context_get_format(&s->output, 0);
    if (ret) {
        av_log(log_ctx, AV_LOG_DEBUG, "v4l2 output format not supported\n");
        goto error;
    }

    ret = ff_v4l2_context_get_format(&s->capture, 0);
    if (ret) {
        av_log(log_ctx, AV_LOG_DEBUG, "v4l2 capture format not supported\n");
        goto error;
    }

    ret = ff_v4l2_context_set_format(&s->output);
    if (ret) {
        av_log(log_ctx, AV_LOG_ERROR, "can't set v4l2 output format\n");
        goto error;
    }

    ret = ff_v4l2_context_set_format(&s->capture);
    if (ret) {
        av_log(log_ctx, AV_LOG_ERROR, "can't to set v4l2 capture format\n");
        goto error;
    }

    ret = ff_v4l2_context_init(&s->output);
    if (ret) {
        av_log(log_ctx, AV_LOG_ERROR, "no v4l2 output context's buffers\n");
        goto error;
    }

    /* decoder's buffers need to be updated at a later stage */
    if (!s->avctx || !av_codec_is_decoder(s->avctx->codec)) {
        ret = ff_v4l2_context_init(&s->capture);
        if (ret) {
            av_log(log_ctx, AV_LOG_ERROR, "no v4l2 capture context's buffers\n");
            goto error;
        }
    }

    return 0;

error:
    return ret;
}