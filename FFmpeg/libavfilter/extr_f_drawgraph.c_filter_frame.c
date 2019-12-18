#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_24__ {int /*<<< orphan*/  value; } ;
struct TYPE_23__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_22__ {scalar_t__ w; int h; TYPE_4__* dst; } ;
struct TYPE_21__ {scalar_t__ width; int height; int* data; int* linesize; int /*<<< orphan*/ * metadata; } ;
struct TYPE_20__ {int slide; int nb_values; int* values_size; float** values; double min; double max; int bg; scalar_t__ x; int mode; int* prev_y; TYPE_2__* out; int /*<<< orphan*/ * first; int /*<<< orphan*/ * fg_expr; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ DrawGraphContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;
typedef  TYPE_5__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_RN32 (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int) ; 
 float NAN ; 
 size_t VAR_MAX ; 
 size_t VAR_MIN ; 
 size_t VAR_VAL ; 
 int VAR_VARS_NB ; 
 float av_clipf (float,double,double) ; 
 TYPE_5__* av_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int av_expr_eval (int /*<<< orphan*/ ,double*,int /*<<< orphan*/ *) ; 
 float* av_fast_realloc (float*,int*,int) ; 
 int /*<<< orphan*/  av_frame_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int av_sscanf (int /*<<< orphan*/ ,char*,float*) ; 
 int /*<<< orphan*/  clear_image (TYPE_1__*,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  draw_dot (int,int,int,TYPE_2__*) ; 
 int ff_filter_frame (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  memmove (int,int,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    DrawGraphContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVDictionary *metadata;
    AVDictionaryEntry *e;
    AVFrame *out = s->out;
    int i;

    if (s->slide == 4 && s->nb_values >= s->values_size[0] / sizeof(float)) {
        float *ptr;

        ptr = av_fast_realloc(s->values[0], &s->values_size[0], s->values_size[0] * 2);
        if (!ptr)
            return AVERROR(ENOMEM);
        s->values[0] = ptr;

        ptr = av_fast_realloc(s->values[1], &s->values_size[1], s->values_size[1] * 2);
        if (!ptr)
            return AVERROR(ENOMEM);
        s->values[1] = ptr;

        ptr = av_fast_realloc(s->values[2], &s->values_size[2], s->values_size[2] * 2);
        if (!ptr)
            return AVERROR(ENOMEM);
        s->values[2] = ptr;

        ptr = av_fast_realloc(s->values[3], &s->values_size[3], s->values_size[3] * 2);
        if (!ptr)
            return AVERROR(ENOMEM);
        s->values[3] = ptr;
    }

    if (s->slide != 4 || s->nb_values == 0) {
        if (!s->out || s->out->width  != outlink->w ||
                       s->out->height != outlink->h) {
            av_frame_free(&s->out);
            s->out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
            out = s->out;
            if (!s->out) {
                av_frame_free(&in);
                return AVERROR(ENOMEM);
            }

            clear_image(s, out, outlink);
        }
        av_frame_copy_props(out, in);
    }

    metadata = in->metadata;

    for (i = 0; i < 4; i++) {
        double values[VAR_VARS_NB];
        int j, y, x, old;
        uint32_t fg, bg;
        float vf;

        if (s->slide == 4)
            s->values[i][s->nb_values] = NAN;

        e = av_dict_get(metadata, s->key[i], NULL, 0);
        if (!e || !e->value)
            continue;

        if (av_sscanf(e->value, "%f", &vf) != 1)
            continue;

        vf = av_clipf(vf, s->min, s->max);

        if (s->slide == 4) {
            s->values[i][s->nb_values] = vf;
            continue;
        }

        values[VAR_MIN] = s->min;
        values[VAR_MAX] = s->max;
        values[VAR_VAL] = vf;

        fg = av_expr_eval(s->fg_expr[i], values, NULL);
        bg = AV_RN32(s->bg);

        if (i == 0 && (s->x >= outlink->w || s->slide == 3)) {
            if (s->slide == 0 || s->slide == 1)
                s->x = 0;

            if (s->slide == 2) {
                s->x = outlink->w - 1;
                for (j = 0; j < outlink->h; j++) {
                    memmove(out->data[0] + j * out->linesize[0] ,
                            out->data[0] + j * out->linesize[0] + 4,
                            (outlink->w - 1) * 4);
                }
            } else if (s->slide == 3) {
                s->x = 0;
                for (j = 0; j < outlink->h; j++) {
                    memmove(out->data[0] + j * out->linesize[0] + 4,
                            out->data[0] + j * out->linesize[0],
                            (outlink->w - 1) * 4);
                }
            } else if (s->slide == 0) {
                clear_image(s, out, outlink);
            }
        }

        x = s->x;
        y = (outlink->h - 1) * (1 - ((vf - s->min) / (s->max - s->min)));

        switch (s->mode) {
        case 0:
            if (i == 0 && (s->slide > 0))
                for (j = 0; j < outlink->h; j++)
                    draw_dot(bg, x, j, out);

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
            if (i == 0 && (s->slide > 0))
                for (j = 0; j < outlink->h; j++)
                    draw_dot(bg, x, j, out);
            draw_dot(fg, x, y, out);
            break;
        case 2:
            if (s->first[i]) {
                s->first[i] = 0;
                s->prev_y[i] = y;
            }

            if (i == 0 && (s->slide > 0)) {
                for (j = 0; j < y; j++)
                    draw_dot(bg, x, j, out);
                for (j = outlink->h - 1; j > y; j--)
                    draw_dot(bg, x, j, out);
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

    s->nb_values++;
    s->x++;

    av_frame_free(&in);

    if (s->slide == 4)
        return 0;

    return ff_filter_frame(outlink, av_frame_clone(s->out));
}