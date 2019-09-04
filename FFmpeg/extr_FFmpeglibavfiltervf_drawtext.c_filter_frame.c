#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_16__ {int frame_count_out; int /*<<< orphan*/  time_base; TYPE_4__* dst; } ;
struct TYPE_15__ {int pts; int pict_type; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  metadata; } ;
struct TYPE_14__ {int* var_values; int start_number; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  metadata; scalar_t__ reload; } ;
typedef  TYPE_1__ DrawTextContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int AV_NOPTS_VALUE ; 
 int NAN ; 
 size_t VAR_N ; 
 size_t VAR_PICT_TYPE ; 
 size_t VAR_T ; 
 size_t VAR_TEXT_H ; 
 size_t VAR_TEXT_W ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_text (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 int load_textfile (TYPE_4__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    DrawTextContext *s = ctx->priv;
    int ret;

    if (s->reload) {
        if ((ret = load_textfile(ctx)) < 0) {
            av_frame_free(&frame);
            return ret;
        }
#if CONFIG_LIBFRIBIDI
        if (s->text_shaping)
            if ((ret = shape_text(ctx)) < 0) {
                av_frame_free(&frame);
                return ret;
            }
#endif
    }

    s->var_values[VAR_N] = inlink->frame_count_out + s->start_number;
    s->var_values[VAR_T] = frame->pts == AV_NOPTS_VALUE ?
        NAN : frame->pts * av_q2d(inlink->time_base);

    s->var_values[VAR_PICT_TYPE] = frame->pict_type;
    s->metadata = frame->metadata;

    draw_text(ctx, frame, frame->width, frame->height);

    av_log(ctx, AV_LOG_DEBUG, "n:%d t:%f text_w:%d text_h:%d x:%d y:%d\n",
           (int)s->var_values[VAR_N], s->var_values[VAR_T],
           (int)s->var_values[VAR_TEXT_W], (int)s->var_values[VAR_TEXT_H],
           s->x, s->y);

    return ff_filter_frame(outlink, frame);
}