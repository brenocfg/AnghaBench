#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_13__ {scalar_t__ format; int /*<<< orphan*/  sample_aspect_ratio; void* frame_pool; TYPE_7__* hw_frames_ctx; } ;
struct TYPE_12__ {int /*<<< orphan*/  sample_aspect_ratio; } ;
struct TYPE_11__ {scalar_t__ format; } ;
typedef  int /*<<< orphan*/  FFFramePool ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 int BUFFER_ALIGN ; 
 int /*<<< orphan*/  av_buffer_allocz ; 
 TYPE_2__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int av_hwframe_get_buffer (TYPE_7__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ff_frame_pool_get (void*) ; 
 scalar_t__ ff_frame_pool_get_video_config (void*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  ff_frame_pool_uninit (int /*<<< orphan*/ **) ; 
 void* ff_frame_pool_video_init (int /*<<< orphan*/ ,int,int,scalar_t__,int) ; 

AVFrame *ff_default_get_video_buffer(AVFilterLink *link, int w, int h)
{
    AVFrame *frame = NULL;
    int pool_width = 0;
    int pool_height = 0;
    int pool_align = 0;
    enum AVPixelFormat pool_format = AV_PIX_FMT_NONE;

    if (link->hw_frames_ctx &&
        ((AVHWFramesContext*)link->hw_frames_ctx->data)->format == link->format) {
        int ret;
        AVFrame *frame = av_frame_alloc();

        if (!frame)
            return NULL;

        ret = av_hwframe_get_buffer(link->hw_frames_ctx, frame, 0);
        if (ret < 0)
            av_frame_free(&frame);

        return frame;
    }

    if (!link->frame_pool) {
        link->frame_pool = ff_frame_pool_video_init(av_buffer_allocz, w, h,
                                                    link->format, BUFFER_ALIGN);
        if (!link->frame_pool)
            return NULL;
    } else {
        if (ff_frame_pool_get_video_config(link->frame_pool,
                                           &pool_width, &pool_height,
                                           &pool_format, &pool_align) < 0) {
            return NULL;
        }

        if (pool_width != w || pool_height != h ||
            pool_format != link->format || pool_align != BUFFER_ALIGN) {

            ff_frame_pool_uninit((FFFramePool **)&link->frame_pool);
            link->frame_pool = ff_frame_pool_video_init(av_buffer_allocz, w, h,
                                                        link->format, BUFFER_ALIGN);
            if (!link->frame_pool)
                return NULL;
        }
    }

    frame = ff_frame_pool_get(link->frame_pool);
    if (!frame)
        return NULL;

    frame->sample_aspect_ratio = link->sample_aspect_ratio;

    return frame;
}