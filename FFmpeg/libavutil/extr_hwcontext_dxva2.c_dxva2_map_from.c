#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ format; } ;
struct TYPE_11__ {scalar_t__ sw_format; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  ENOSYS ; 
 int av_frame_copy_props (TYPE_2__*,TYPE_2__ const*) ; 
 int dxva2_map_frame (TYPE_1__*,TYPE_2__*,TYPE_2__ const*,int) ; 

__attribute__((used)) static int dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, const AVFrame *src, int flags)
{
    int err;

    if (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        return AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_frame(ctx, dst, src, flags);
    if (err < 0)
        return err;

    err = av_frame_copy_props(dst, src);
    if (err < 0)
        return err;

    return 0;
}