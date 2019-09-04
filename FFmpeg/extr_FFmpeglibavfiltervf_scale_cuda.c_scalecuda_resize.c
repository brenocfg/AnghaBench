#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* priv; } ;
struct TYPE_13__ {int* data; int width; int height; int* linesize; TYPE_1__* hw_frames_ctx; } ;
struct TYPE_12__ {int sw_format; } ;
struct TYPE_11__ {int /*<<< orphan*/  cu_func_ushort2; int /*<<< orphan*/  cu_func_ushort; int /*<<< orphan*/  cu_func_uchar2; int /*<<< orphan*/  cu_func_uchar; int /*<<< orphan*/  tex_alignment; } ;
struct TYPE_10__ {scalar_t__ data; } ;
typedef  TYPE_2__ CUDAScaleContext ;
typedef  TYPE_3__ AVHWFramesContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int ALIGN_UP (int,int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
#define  AV_PIX_FMT_NV12 132 
#define  AV_PIX_FMT_P010LE 131 
#define  AV_PIX_FMT_P016LE 130 
#define  AV_PIX_FMT_YUV420P 129 
#define  AV_PIX_FMT_YUV444P 128 
 int /*<<< orphan*/  call_resize_kernel (TYPE_5__*,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static int scalecuda_resize(AVFilterContext *ctx,
                            AVFrame *out, AVFrame *in)
{
    AVHWFramesContext *in_frames_ctx = (AVHWFramesContext*)in->hw_frames_ctx->data;
    CUDAScaleContext *s = ctx->priv;

    switch (in_frames_ctx->sw_format) {
    case AV_PIX_FMT_YUV420P:
        call_resize_kernel(ctx, s->cu_func_uchar, 1,
                           in->data[0], in->width, in->height, in->linesize[0],
                           out->data[0], out->width, out->height, out->linesize[0],
                           1);
        call_resize_kernel(ctx, s->cu_func_uchar, 1,
                           in->data[0]+in->linesize[0]*in->height, in->width/2, in->height/2, in->linesize[0]/2,
                           out->data[0]+out->linesize[0]*out->height, out->width/2, out->height/2, out->linesize[0]/2,
                           1);
        call_resize_kernel(ctx, s->cu_func_uchar, 1,
                           in->data[0]+ ALIGN_UP((in->linesize[0]*in->height*5)/4, s->tex_alignment), in->width/2, in->height/2, in->linesize[0]/2,
                           out->data[0]+(out->linesize[0]*out->height*5)/4, out->width/2, out->height/2, out->linesize[0]/2,
                           1);
        break;
    case AV_PIX_FMT_YUV444P:
        call_resize_kernel(ctx, s->cu_func_uchar, 1,
                           in->data[0], in->width, in->height, in->linesize[0],
                           out->data[0], out->width, out->height, out->linesize[0],
                           1);
        call_resize_kernel(ctx, s->cu_func_uchar, 1,
                           in->data[0]+in->linesize[0]*in->height, in->width, in->height, in->linesize[0],
                           out->data[0]+out->linesize[0]*out->height, out->width, out->height, out->linesize[0],
                           1);
        call_resize_kernel(ctx, s->cu_func_uchar, 1,
                           in->data[0]+in->linesize[0]*in->height*2, in->width, in->height, in->linesize[0],
                           out->data[0]+out->linesize[0]*out->height*2, out->width, out->height, out->linesize[0],
                           1);
        break;
    case AV_PIX_FMT_NV12:
        call_resize_kernel(ctx, s->cu_func_uchar, 1,
                           in->data[0], in->width, in->height, in->linesize[0],
                           out->data[0], out->width, out->height, out->linesize[0],
                           1);
        call_resize_kernel(ctx, s->cu_func_uchar2, 2,
                           in->data[1], in->width/2, in->height/2, in->linesize[1],
                           out->data[0] + out->linesize[0] * ((out->height + 31) & ~0x1f), out->width/2, out->height/2, out->linesize[1]/2,
                           1);
        break;
    case AV_PIX_FMT_P010LE:
        call_resize_kernel(ctx, s->cu_func_ushort, 1,
                           in->data[0], in->width, in->height, in->linesize[0]/2,
                           out->data[0], out->width, out->height, out->linesize[0]/2,
                           2);
        call_resize_kernel(ctx, s->cu_func_ushort2, 2,
                           in->data[1], in->width / 2, in->height / 2, in->linesize[1]/2,
                           out->data[0] + out->linesize[0] * ((out->height + 31) & ~0x1f), out->width / 2, out->height / 2, out->linesize[1] / 4,
                           2);
        break;
    case AV_PIX_FMT_P016LE:
        call_resize_kernel(ctx, s->cu_func_ushort, 1,
                           in->data[0], in->width, in->height, in->linesize[0] / 2,
                           out->data[0], out->width, out->height, out->linesize[0] / 2,
                           2);
        call_resize_kernel(ctx, s->cu_func_ushort2, 2,
                           in->data[1], in->width / 2, in->height / 2, in->linesize[1] / 2,
                           out->data[0] + out->linesize[0] * ((out->height + 31) & ~0x1f), out->width / 2, out->height / 2, out->linesize[1] / 4,
                           2);
        break;
    default:
        return AVERROR_BUG;
    }

    return 0;
}