#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/ * outputs; int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_10__ {int h; TYPE_4__* src; } ;
struct TYPE_9__ {int* data; int* linesize; scalar_t__ pts; } ;
struct TYPE_8__ {int slide; float nb_values; int x; float** values; double min; double max; int mode; int* prev_y; TYPE_2__* out; int /*<<< orphan*/ * first; int /*<<< orphan*/  bg; int /*<<< orphan*/ * fg_expr; scalar_t__ w; } ;
typedef  TYPE_1__ DrawGraphContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AV_RN32 (int /*<<< orphan*/ ) ; 
 int FFMIN (int,int) ; 
 size_t VAR_MAX ; 
 size_t VAR_MIN ; 
 size_t VAR_VAL ; 
 int VAR_VARS_NB ; 
 int av_expr_eval (int /*<<< orphan*/ ,double*,int /*<<< orphan*/ *) ; 
 int ceil (float) ; 
 int /*<<< orphan*/  draw_dot (int,int,int,TYPE_2__*) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (float) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    DrawGraphContext *s = ctx->priv;
    AVFrame *out = s->out;
    int ret, i, k, step, l;

    ret = ff_request_frame(ctx->inputs[0]);

    if (s->slide == 4 && ret == AVERROR_EOF && s->nb_values > 0) {
        s->x = l = 0;
        step = ceil(s->nb_values / (float)s->w);

        for (k = 0; k < s->nb_values; k++) {
            for (i = 0; i < 4; i++) {
                double values[VAR_VARS_NB];
                int j, y, x, old;
                uint32_t fg, bg;
                float vf = s->values[i][k];

                if (isnan(vf))
                    continue;

                values[VAR_MIN] = s->min;
                values[VAR_MAX] = s->max;
                values[VAR_VAL] = vf;

                fg = av_expr_eval(s->fg_expr[i], values, NULL);
                bg = AV_RN32(s->bg);

                x = s->x;
                y = (outlink->h - 1) * (1 - ((vf - s->min) / (s->max - s->min)));

                switch (s->mode) {
                case 0:
                    old = AV_RN32(out->data[0] + y * out->linesize[0] + x * 4);
                    for (j = y; j < outlink->h; j++) {
                        if (old != bg &&
                            (AV_RN32(out->data[0] + j * out->linesize[0] + x * 4) != old) ||
                            AV_RN32(out->data[0] + FFMIN(j+1, outlink->h - 1) * out->linesize[0] + x * 4) != old) {
                            draw_dot(fg, x, j, out);
                            break;
                        }
                        draw_dot(fg, x, j, out);
                    }
                    break;
                case 1:
                    draw_dot(fg, x, y, out);
                    break;
                case 2:
                    if (s->first[i]) {
                        s->first[i] = 0;
                        s->prev_y[i] = y;
                    }

                    if (y <= s->prev_y[i]) {
                        for (j = y; j <= s->prev_y[i]; j++)
                            draw_dot(fg, x, j, out);
                    } else {
                        for (j = s->prev_y[i]; j <= y; j++)
                            draw_dot(fg, x, j, out);
                    }
                    s->prev_y[i] = y;
                    break;
                }
            }

            l++;
            if (l >= step) {
                l = 0;
                s->x++;
            }
        }

        s->nb_values = 0;
        out->pts = 0;
        ret = ff_filter_frame(ctx->outputs[0], s->out);
    }

    return ret;
}