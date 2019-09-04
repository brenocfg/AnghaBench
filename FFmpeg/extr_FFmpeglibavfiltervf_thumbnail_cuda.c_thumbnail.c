#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cu_func_ushort2; int /*<<< orphan*/  cu_func_ushort; int /*<<< orphan*/  cu_func_uchar; int /*<<< orphan*/  cu_func_uchar2; } ;
typedef  TYPE_2__ ThumbnailCudaContext ;
struct TYPE_13__ {TYPE_2__* priv; } ;
struct TYPE_12__ {int width; int height; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; TYPE_1__* hw_frames_ctx; } ;
struct TYPE_11__ {int sw_format; } ;
struct TYPE_9__ {scalar_t__ data; } ;
typedef  TYPE_3__ AVHWFramesContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
#define  AV_PIX_FMT_NV12 133 
#define  AV_PIX_FMT_P010LE 132 
#define  AV_PIX_FMT_P016LE 131 
#define  AV_PIX_FMT_YUV420P 130 
#define  AV_PIX_FMT_YUV444P 129 
#define  AV_PIX_FMT_YUV444P16 128 
 int /*<<< orphan*/  thumbnail_kernel (TYPE_5__*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int thumbnail(AVFilterContext *ctx, int *histogram, AVFrame *in)
{
    AVHWFramesContext *in_frames_ctx = (AVHWFramesContext*)in->hw_frames_ctx->data;
    ThumbnailCudaContext *s = ctx->priv;

    switch (in_frames_ctx->sw_format) {
    case AV_PIX_FMT_NV12:
        thumbnail_kernel(ctx, s->cu_func_uchar, 1,
            histogram, in->data[0], in->width, in->height, in->linesize[0], 1);
        thumbnail_kernel(ctx, s->cu_func_uchar2, 2,
            histogram + 256, in->data[1], in->width / 2, in->height / 2, in->linesize[1], 1);
        break;
    case AV_PIX_FMT_YUV420P:
        thumbnail_kernel(ctx, s->cu_func_uchar, 1,
            histogram, in->data[0], in->width, in->height, in->linesize[0], 1);
        thumbnail_kernel(ctx, s->cu_func_uchar, 1,
            histogram + 256, in->data[1], in->width / 2, in->height / 2, in->linesize[1], 1);
        thumbnail_kernel(ctx, s->cu_func_uchar, 1,
            histogram + 512, in->data[2], in->width / 2, in->height / 2, in->linesize[2], 1);
        break;
    case AV_PIX_FMT_YUV444P:
        thumbnail_kernel(ctx, s->cu_func_uchar, 1,
            histogram, in->data[0], in->width, in->height, in->linesize[0], 1);
        thumbnail_kernel(ctx, s->cu_func_uchar, 1,
            histogram + 256, in->data[1], in->width, in->height, in->linesize[1], 1);
        thumbnail_kernel(ctx, s->cu_func_uchar, 1,
            histogram + 512, in->data[2], in->width, in->height, in->linesize[2], 1);
        break;
    case AV_PIX_FMT_P010LE:
    case AV_PIX_FMT_P016LE:
        thumbnail_kernel(ctx, s->cu_func_ushort, 1,
            histogram, in->data[0], in->width, in->height, in->linesize[0], 2);
        thumbnail_kernel(ctx, s->cu_func_ushort2, 2,
            histogram + 256, in->data[1], in->width / 2, in->height / 2, in->linesize[1], 2);
        break;
    case AV_PIX_FMT_YUV444P16:
        thumbnail_kernel(ctx, s->cu_func_ushort2, 1,
            histogram, in->data[0], in->width, in->height, in->linesize[0], 2);
        thumbnail_kernel(ctx, s->cu_func_ushort2, 1,
            histogram + 256, in->data[1], in->width, in->height, in->linesize[1], 2);
        thumbnail_kernel(ctx, s->cu_func_ushort2, 1,
            histogram + 512, in->data[2], in->width, in->height, in->linesize[2], 2);
        break;
    default:
        return AVERROR_BUG;
    }

    return 0;
}