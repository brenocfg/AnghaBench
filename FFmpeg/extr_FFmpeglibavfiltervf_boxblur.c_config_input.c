#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  power; int /*<<< orphan*/  radius; } ;
struct TYPE_17__ {int /*<<< orphan*/  power; int /*<<< orphan*/  radius; } ;
struct TYPE_16__ {int /*<<< orphan*/  power; int /*<<< orphan*/  radius; } ;
struct TYPE_15__ {TYPE_1__* priv; } ;
struct TYPE_14__ {int w; int h; TYPE_4__* dst; int /*<<< orphan*/  format; } ;
struct TYPE_13__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
struct TYPE_12__ {TYPE_8__ alpha_param; int /*<<< orphan*/ * power; TYPE_7__ chroma_param; TYPE_6__ luma_param; int /*<<< orphan*/ * radius; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; void** temp; } ;
typedef  TYPE_1__ BoxBlurContext ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 size_t A ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
 size_t U ; 
 size_t V ; 
 size_t Y ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 void* av_malloc (int) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int ff_boxblur_eval_filter_params (TYPE_3__*,TYPE_6__*,TYPE_7__*,TYPE_8__*) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    AVFilterContext    *ctx = inlink->dst;
    BoxBlurContext *s = ctx->priv;
    int w = inlink->w, h = inlink->h;
    int ret;

    if (!(s->temp[0] = av_malloc(2*FFMAX(w, h))) ||
        !(s->temp[1] = av_malloc(2*FFMAX(w, h))))
        return AVERROR(ENOMEM);

    s->hsub = desc->log2_chroma_w;
    s->vsub = desc->log2_chroma_h;

    ret = ff_boxblur_eval_filter_params(inlink,
                                        &s->luma_param,
                                        &s->chroma_param,
                                        &s->alpha_param);

    if (ret != 0) {
        av_log(ctx, AV_LOG_ERROR, "Failed to evaluate "
               "filter params: %d.\n", ret);
        return ret;
    }

    s->radius[Y] = s->luma_param.radius;
    s->radius[U] = s->radius[V] = s->chroma_param.radius;
    s->radius[A] = s->alpha_param.radius;

    s->power[Y] = s->luma_param.power;
    s->power[U] = s->power[V] = s->chroma_param.power;
    s->power[A] = s->alpha_param.power;

    return 0;
}