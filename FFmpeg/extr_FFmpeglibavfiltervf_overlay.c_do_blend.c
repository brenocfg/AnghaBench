#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_19__ {TYPE_5__* src; TYPE_5__* dst; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_24__ {int /*<<< orphan*/ * outputs; TYPE_1__* internal; TYPE_6__** inputs; TYPE_3__* priv; } ;
struct TYPE_23__ {int frame_count_out; int /*<<< orphan*/  time_base; } ;
struct TYPE_22__ {int pkt_pos; int pts; scalar_t__ width; scalar_t__ height; } ;
struct TYPE_21__ {TYPE_7__* parent; } ;
struct TYPE_20__ {scalar_t__ eval_mode; int* var_values; scalar_t__ x; scalar_t__ y; int /*<<< orphan*/  blend_slice; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* execute ) (TYPE_7__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ OverlayContext ;
typedef  TYPE_4__ FFFrameSync ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterLink ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int AV_NOPTS_VALUE ; 
 scalar_t__ EVAL_MODE_FRAME ; 
 scalar_t__ FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FFMIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FFMIN3 (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int NAN ; 
 size_t VAR_MAIN_H ; 
 size_t VAR_MAIN_W ; 
 size_t VAR_MH ; 
 size_t VAR_MW ; 
 size_t VAR_N ; 
 size_t VAR_OH ; 
 size_t VAR_OVERLAY_H ; 
 size_t VAR_OVERLAY_W ; 
 size_t VAR_OW ; 
 size_t VAR_POS ; 
 size_t VAR_T ; 
 size_t VAR_X ; 
 size_t VAR_Y ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eval_expr (TYPE_7__*) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ ff_filter_get_nb_threads (TYPE_7__*) ; 
 int ff_framesync_dualinput_get_writable (TYPE_4__*,TYPE_5__**,TYPE_5__**) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_blend(FFFrameSync *fs)
{
    AVFilterContext *ctx = fs->parent;
    AVFrame *mainpic, *second;
    OverlayContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    int ret;

    ret = ff_framesync_dualinput_get_writable(fs, &mainpic, &second);
    if (ret < 0)
        return ret;
    if (!second)
        return ff_filter_frame(ctx->outputs[0], mainpic);

    if (s->eval_mode == EVAL_MODE_FRAME) {
        int64_t pos = mainpic->pkt_pos;

        s->var_values[VAR_N] = inlink->frame_count_out;
        s->var_values[VAR_T] = mainpic->pts == AV_NOPTS_VALUE ?
            NAN : mainpic->pts * av_q2d(inlink->time_base);
        s->var_values[VAR_POS] = pos == -1 ? NAN : pos;

        s->var_values[VAR_OVERLAY_W] = s->var_values[VAR_OW] = second->width;
        s->var_values[VAR_OVERLAY_H] = s->var_values[VAR_OH] = second->height;
        s->var_values[VAR_MAIN_W   ] = s->var_values[VAR_MW] = mainpic->width;
        s->var_values[VAR_MAIN_H   ] = s->var_values[VAR_MH] = mainpic->height;

        eval_expr(ctx);
        av_log(ctx, AV_LOG_DEBUG, "n:%f t:%f pos:%f x:%f xi:%d y:%f yi:%d\n",
               s->var_values[VAR_N], s->var_values[VAR_T], s->var_values[VAR_POS],
               s->var_values[VAR_X], s->x,
               s->var_values[VAR_Y], s->y);
    }

    if (s->x < mainpic->width  && s->x + second->width  >= 0 &&
        s->y < mainpic->height && s->y + second->height >= 0) {
        ThreadData td;

        td.dst = mainpic;
        td.src = second;
        ctx->internal->execute(ctx, s->blend_slice, &td, NULL, FFMIN(FFMAX(1, FFMIN3(s->y + second->height, FFMIN(second->height, mainpic->height), mainpic->height - s->y)),
                                                                     ff_filter_get_nb_threads(ctx)));
    }
    return ff_filter_frame(ctx->outputs[0], mainpic);
}