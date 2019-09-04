#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_5__ {int initial_pool_size; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ ***) ; 
 int av_hwframe_get_buffer (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** av_mallocz_array (int,int) ; 

__attribute__((used)) static int hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    int i, ret = 0;

    frames = av_mallocz_array(ctx->initial_pool_size, sizeof(*frames));
    if (!frames)
        return AVERROR(ENOMEM);

    for (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        if (!frames[i])
            goto fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        if (ret < 0)
            goto fail;
    }

fail:
    for (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    return ret;
}