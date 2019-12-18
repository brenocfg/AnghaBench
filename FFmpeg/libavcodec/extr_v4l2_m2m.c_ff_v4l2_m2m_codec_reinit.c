#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ reinit; scalar_t__ draining; int /*<<< orphan*/  capture; int /*<<< orphan*/  refsync; int /*<<< orphan*/  refcount; void* priv; } ;
typedef  TYPE_1__ V4L2m2mContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  VIDIOC_STREAMOFF ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int ff_v4l2_context_get_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_v4l2_context_release (int /*<<< orphan*/ *) ; 
 int ff_v4l2_context_set_format (int /*<<< orphan*/ *) ; 
 int ff_v4l2_context_set_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sem_wait (int /*<<< orphan*/ *) ; 

int ff_v4l2_m2m_codec_reinit(V4L2m2mContext* s)
{
    void *log_ctx = s->priv;
    int ret;

    av_log(log_ctx, AV_LOG_DEBUG, "reinit context\n");

    /* 1. streamoff */
    ret = ff_v4l2_context_set_status(&s->capture, VIDIOC_STREAMOFF);
    if (ret)
        av_log(log_ctx, AV_LOG_ERROR, "capture VIDIOC_STREAMOFF\n");

    /* 2. unmap the capture buffers (v4l2 and ffmpeg):
     *    we must wait for all references to be released before being allowed
     *    to queue new buffers.
     */
    av_log(log_ctx, AV_LOG_DEBUG, "waiting for user to release AVBufferRefs\n");
    if (atomic_load(&s->refcount))
        while(sem_wait(&s->refsync) == -1 && errno == EINTR);

    ff_v4l2_context_release(&s->capture);

    /* 3. get the new capture format */
    ret = ff_v4l2_context_get_format(&s->capture, 0);
    if (ret) {
        av_log(log_ctx, AV_LOG_ERROR, "query the new capture format\n");
        return ret;
    }

    /* 4. set the capture format */
    ret = ff_v4l2_context_set_format(&s->capture);
    if (ret) {
        av_log(log_ctx, AV_LOG_ERROR, "setting capture format\n");
        return ret;
    }

    /* 5. complete reinit */
    s->draining = 0;
    s->reinit = 0;

    return 0;
}