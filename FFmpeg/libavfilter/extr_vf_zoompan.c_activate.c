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
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_21__ {int* var_values; int w; int h; int x; int y; int prev_zoom; int prev_nb_frames; double nb_frames; scalar_t__ finished; int /*<<< orphan*/  current_frame; TYPE_7__* in; int /*<<< orphan*/  duration_expr_str; TYPE_2__* desc; } ;
typedef  TYPE_3__ ZPContext ;
struct TYPE_24__ {int width; int height; } ;
struct TYPE_23__ {TYPE_4__** outputs; TYPE_4__** inputs; TYPE_3__* priv; } ;
struct TYPE_19__ {double den; scalar_t__ num; } ;
struct TYPE_22__ {int frame_count_out; int frame_count_in; TYPE_1__ sample_aspect_ratio; } ;
struct TYPE_20__ {int log2_chroma_w; int log2_chroma_h; } ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (TYPE_4__*,TYPE_4__*) ; 
 size_t VAR_A ; 
 size_t VAR_DAR ; 
 size_t VAR_DURATION ; 
 size_t VAR_HSUB ; 
 size_t VAR_IH ; 
 size_t VAR_IN ; 
 size_t VAR_IN_H ; 
 size_t VAR_IN_W ; 
 size_t VAR_IW ; 
 size_t VAR_OH ; 
 size_t VAR_ON ; 
 size_t VAR_OUT_H ; 
 size_t VAR_OUT_W ; 
 size_t VAR_OW ; 
 size_t VAR_PDURATION ; 
 size_t VAR_PX ; 
 size_t VAR_PY ; 
 size_t VAR_PZOOM ; 
 size_t VAR_SAR ; 
 size_t VAR_VSUB ; 
 size_t VAR_X ; 
 size_t VAR_Y ; 
 size_t VAR_ZOOM ; 
 int av_expr_parse_and_eval (double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_7__**) ; 
 scalar_t__ ff_inlink_acknowledge_status (TYPE_4__*,int*,int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_frame (TYPE_4__*,TYPE_7__**) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (TYPE_4__*) ; 
 scalar_t__ ff_outlink_frame_wanted (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_outlink_set_status (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int output_single_frame (TYPE_5__*,TYPE_7__*,int*,int /*<<< orphan*/ ,double*,double*,double*) ; 
 int /*<<< orphan*/  var_names ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    ZPContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    int status, ret = 0;
    int64_t pts;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    if (s->in && ff_outlink_frame_wanted(outlink)) {
        double zoom = -1, dx = -1, dy = -1;

        ret = output_single_frame(ctx, s->in, s->var_values, s->current_frame,
                                  &zoom, &dx, &dy);
        if (ret < 0)
            return ret;
    }

    if (!s->in && (ret = ff_inlink_consume_frame(inlink, &s->in)) > 0) {
        double zoom = -1, dx = -1, dy = -1, nb_frames;

        s->finished = 0;
        s->var_values[VAR_IN_W]  = s->var_values[VAR_IW] = s->in->width;
        s->var_values[VAR_IN_H]  = s->var_values[VAR_IH] = s->in->height;
        s->var_values[VAR_OUT_W] = s->var_values[VAR_OW] = s->w;
        s->var_values[VAR_OUT_H] = s->var_values[VAR_OH] = s->h;
        s->var_values[VAR_IN]    = inlink->frame_count_out - 1;
        s->var_values[VAR_ON]    = outlink->frame_count_in;
        s->var_values[VAR_PX]    = s->x;
        s->var_values[VAR_PY]    = s->y;
        s->var_values[VAR_X]     = 0;
        s->var_values[VAR_Y]     = 0;
        s->var_values[VAR_PZOOM] = s->prev_zoom;
        s->var_values[VAR_ZOOM]  = 1;
        s->var_values[VAR_PDURATION] = s->prev_nb_frames;
        s->var_values[VAR_A]     = (double) s->in->width / s->in->height;
        s->var_values[VAR_SAR]   = inlink->sample_aspect_ratio.num ?
            (double) inlink->sample_aspect_ratio.num / inlink->sample_aspect_ratio.den : 1;
        s->var_values[VAR_DAR]   = s->var_values[VAR_A] * s->var_values[VAR_SAR];
        s->var_values[VAR_HSUB]  = 1 << s->desc->log2_chroma_w;
        s->var_values[VAR_VSUB]  = 1 << s->desc->log2_chroma_h;

        if ((ret = av_expr_parse_and_eval(&nb_frames, s->duration_expr_str,
                                          var_names, s->var_values,
                                          NULL, NULL, NULL, NULL, NULL, 0, ctx)) < 0) {
            av_frame_free(&s->in);
            return ret;
        }

        s->var_values[VAR_DURATION] = s->nb_frames = nb_frames;

        ret = output_single_frame(ctx, s->in, s->var_values, s->current_frame,
                                  &zoom, &dx, &dy);
        if (ret < 0)
            return ret;
    }
    if (ret < 0) {
        return ret;
    } else if (s->finished && ff_inlink_acknowledge_status(inlink, &status, &pts)) {
        ff_outlink_set_status(outlink, status, pts);
        return 0;
    } else {
        if (ff_outlink_frame_wanted(outlink) && s->finished)
            ff_inlink_request_frame(inlink);
        return 0;
    }
}