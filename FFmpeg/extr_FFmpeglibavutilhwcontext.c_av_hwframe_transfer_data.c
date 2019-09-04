#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_1__* hw_frames_ctx; int /*<<< orphan*/ * buf; } ;
struct TYPE_19__ {TYPE_3__* internal; } ;
struct TYPE_18__ {TYPE_2__* hw_type; } ;
struct TYPE_17__ {int (* transfer_data_from ) (TYPE_4__*,TYPE_5__*,TYPE_5__ const*) ;int (* transfer_data_to ) (TYPE_4__*,TYPE_5__*,TYPE_5__ const*) ;} ;
struct TYPE_16__ {scalar_t__ data; } ;
typedef  TYPE_4__ AVHWFramesContext ;
typedef  TYPE_5__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int stub1 (TYPE_4__*,TYPE_5__*,TYPE_5__ const*) ; 
 int stub2 (TYPE_4__*,TYPE_5__*,TYPE_5__ const*) ; 
 int transfer_data_alloc (TYPE_5__*,TYPE_5__ const*,int) ; 

int av_hwframe_transfer_data(AVFrame *dst, const AVFrame *src, int flags)
{
    AVHWFramesContext *ctx;
    int ret;

    if (!dst->buf[0])
        return transfer_data_alloc(dst, src, flags);

    if (src->hw_frames_ctx) {
        ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

        ret = ctx->internal->hw_type->transfer_data_from(ctx, dst, src);
        if (ret < 0)
            return ret;
    } else if (dst->hw_frames_ctx) {
        ctx = (AVHWFramesContext*)dst->hw_frames_ctx->data;

        ret = ctx->internal->hw_type->transfer_data_to(ctx, dst, src);
        if (ret < 0)
            return ret;
    } else
        return AVERROR(ENOSYS);

    return 0;
}