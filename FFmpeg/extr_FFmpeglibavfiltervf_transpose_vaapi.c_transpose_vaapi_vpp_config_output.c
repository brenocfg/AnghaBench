#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ passthrough; int dir; scalar_t__ output_width; scalar_t__ output_height; } ;
typedef  TYPE_1__ VAAPIVPPContext ;
typedef  TYPE_1__ TransposeVAAPIContext ;
struct TYPE_10__ {TYPE_3__** inputs; TYPE_1__* priv; } ;
struct TYPE_9__ {scalar_t__ w; scalar_t__ h; int /*<<< orphan*/  hw_frames_ctx; TYPE_4__* src; } ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  TRANSPOSE_CCLOCK 131 
#define  TRANSPOSE_CCLOCK_FLIP 130 
#define  TRANSPOSE_CLOCK 129 
#define  TRANSPOSE_CLOCK_FLIP 128 
 scalar_t__ TRANSPOSE_PT_TYPE_LANDSCAPE ; 
 scalar_t__ TRANSPOSE_PT_TYPE_NONE ; 
 scalar_t__ TRANSPOSE_PT_TYPE_PORTRAIT ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_vaapi_vpp_config_output (TYPE_3__*) ; 

__attribute__((used)) static int transpose_vaapi_vpp_config_output(AVFilterLink *outlink)
{
    AVFilterContext *avctx     = outlink->src;
    VAAPIVPPContext *vpp_ctx   = avctx->priv;
    TransposeVAAPIContext *ctx = avctx->priv;
    AVFilterLink *inlink       = avctx->inputs[0];

    if ((inlink->w >= inlink->h && ctx->passthrough == TRANSPOSE_PT_TYPE_LANDSCAPE) ||
        (inlink->w <= inlink->h && ctx->passthrough == TRANSPOSE_PT_TYPE_PORTRAIT)) {
        outlink->hw_frames_ctx = av_buffer_ref(inlink->hw_frames_ctx);
        if (!outlink->hw_frames_ctx)
            return AVERROR(ENOMEM);
        av_log(avctx, AV_LOG_VERBOSE,
               "w:%d h:%d -> w:%d h:%d (passthrough mode)\n",
               inlink->w, inlink->h, inlink->w, inlink->h);
        return 0;
    }

    ctx->passthrough = TRANSPOSE_PT_TYPE_NONE;

    switch (ctx->dir) {
    case TRANSPOSE_CCLOCK_FLIP:
    case TRANSPOSE_CCLOCK:
    case TRANSPOSE_CLOCK:
    case TRANSPOSE_CLOCK_FLIP:
        vpp_ctx->output_width  = avctx->inputs[0]->h;
        vpp_ctx->output_height = avctx->inputs[0]->w;
        av_log(avctx, AV_LOG_DEBUG, "swap width and height for clock/cclock rotation\n");
        break;
    default:
        break;
    }

    return ff_vaapi_vpp_config_output(outlink);
}