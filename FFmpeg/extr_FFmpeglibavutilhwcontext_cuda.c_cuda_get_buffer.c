#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int* linesize; int height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; scalar_t__* data; TYPE_5__** buf; } ;
struct TYPE_6__ {scalar_t__ sw_format; int height; int /*<<< orphan*/  width; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PIX_FMT_CUDA ; 
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  CUDA_FRAME_ALIGNMENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_5__* av_buffer_pool_get (int /*<<< orphan*/ ) ; 
 int av_image_fill_arrays (scalar_t__*,int*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cuda_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    int res;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    if (!frame->buf[0])
        return AVERROR(ENOMEM);

    res = av_image_fill_arrays(frame->data, frame->linesize, frame->buf[0]->data,
                               ctx->sw_format, ctx->width, ctx->height, CUDA_FRAME_ALIGNMENT);
    if (res < 0)
        return res;

    // YUV420P is a special case.
    // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
    if (ctx->sw_format == AV_PIX_FMT_YUV420P) {
        frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
        frame->data[2]     = frame->data[1];
        frame->data[1]     = frame->data[2] + frame->linesize[2] * ctx->height / 2;
    }

    frame->format = AV_PIX_FMT_CUDA;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    return 0;
}