#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ data; } ;
struct TYPE_10__ {TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  hw_frames_ctx; TYPE_3__* dst; } ;
struct TYPE_8__ {TYPE_6__* hwframes_ref; int /*<<< orphan*/ * hwframes; } ;
typedef  TYPE_1__ HWDownloadContext ;
typedef  int /*<<< orphan*/  AVHWFramesContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_6__* av_buffer_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_6__**) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hwdownload_config_input(AVFilterLink *inlink)
{
    AVFilterContext *avctx = inlink->dst;
    HWDownloadContext *ctx = avctx->priv;

    av_buffer_unref(&ctx->hwframes_ref);

    if (!inlink->hw_frames_ctx) {
        av_log(ctx, AV_LOG_ERROR, "The input must have a hardware frame "
               "reference.\n");
        return AVERROR(EINVAL);
    }

    ctx->hwframes_ref = av_buffer_ref(inlink->hw_frames_ctx);
    if (!ctx->hwframes_ref)
        return AVERROR(ENOMEM);

    ctx->hwframes = (AVHWFramesContext*)ctx->hwframes_ref->data;

    return 0;
}