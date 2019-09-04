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
struct TYPE_13__ {size_t nb_outputs; TYPE_1__* input_pads; TYPE_4__** inputs; TYPE_3__* priv; } ;
struct TYPE_10__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_12__ {scalar_t__ w; scalar_t__ h; TYPE_2__ sample_aspect_ratio; int /*<<< orphan*/  format; int /*<<< orphan*/  time_base; TYPE_5__* src; } ;
struct TYPE_11__ {unsigned int nb_segments; int /*<<< orphan*/  unsafe; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ ConcatContext ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  EINVAL ; 
 unsigned int FF_OUTLINK_IDX (TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    ConcatContext *cat   = ctx->priv;
    unsigned out_no = FF_OUTLINK_IDX(outlink);
    unsigned in_no  = out_no, seg;
    AVFilterLink *inlink = ctx->inputs[in_no];

    /* enhancement: find a common one */
    outlink->time_base           = AV_TIME_BASE_Q;
    outlink->w                   = inlink->w;
    outlink->h                   = inlink->h;
    outlink->sample_aspect_ratio = inlink->sample_aspect_ratio;
    outlink->format              = inlink->format;
    for (seg = 1; seg < cat->nb_segments; seg++) {
        inlink = ctx->inputs[in_no += ctx->nb_outputs];
        if (!outlink->sample_aspect_ratio.num)
            outlink->sample_aspect_ratio = inlink->sample_aspect_ratio;
        /* possible enhancement: unsafe mode, do not check */
        if (outlink->w                       != inlink->w                       ||
            outlink->h                       != inlink->h                       ||
            outlink->sample_aspect_ratio.num != inlink->sample_aspect_ratio.num &&
                                                inlink->sample_aspect_ratio.num ||
            outlink->sample_aspect_ratio.den != inlink->sample_aspect_ratio.den) {
            av_log(ctx, AV_LOG_ERROR, "Input link %s parameters "
                   "(size %dx%d, SAR %d:%d) do not match the corresponding "
                   "output link %s parameters (%dx%d, SAR %d:%d)\n",
                   ctx->input_pads[in_no].name, inlink->w, inlink->h,
                   inlink->sample_aspect_ratio.num,
                   inlink->sample_aspect_ratio.den,
                   ctx->input_pads[out_no].name, outlink->w, outlink->h,
                   outlink->sample_aspect_ratio.num,
                   outlink->sample_aspect_ratio.den);
            if (!cat->unsafe)
                return AVERROR(EINVAL);
        }
    }

    return 0;
}