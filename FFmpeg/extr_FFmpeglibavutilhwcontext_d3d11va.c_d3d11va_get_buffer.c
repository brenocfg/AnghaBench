#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {scalar_t__ data; } ;
struct TYPE_9__ {scalar_t__ index; scalar_t__ texture; } ;
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; int /*<<< orphan*/ ** data; TYPE_6__** buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVD3D11FrameDescriptor ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PIX_FMT_D3D11 ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_6__* av_buffer_pool_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int d3d11va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    if (!frame->buf[0])
        return AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->data;

    frame->data[0] = (uint8_t *)desc->texture;
    frame->data[1] = (uint8_t *)desc->index;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    return 0;
}