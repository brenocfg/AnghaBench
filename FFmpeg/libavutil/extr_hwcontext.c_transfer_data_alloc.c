#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_15__ {scalar_t__ data; } ;
struct TYPE_14__ {scalar_t__ format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_5__* hw_frames_ctx; } ;
struct TYPE_13__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_HWFRAME_TRANSFER_DIRECTION_FROM ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int av_frame_get_buffer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_frame_move_ref (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int av_hwframe_transfer_data (TYPE_2__*,TYPE_2__ const*,int) ; 
 int av_hwframe_transfer_get_formats (TYPE_5__*,int /*<<< orphan*/ ,int**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transfer_data_alloc(AVFrame *dst, const AVFrame *src, int flags)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVFrame *frame_tmp;
    int ret = 0;

    frame_tmp = av_frame_alloc();
    if (!frame_tmp)
        return AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    if (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } else {
        enum AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        if (ret < 0)
            goto fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_frame_get_buffer(frame_tmp, 32);
    if (ret < 0)
        goto fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    if (ret < 0)
        goto fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    return ret;
}