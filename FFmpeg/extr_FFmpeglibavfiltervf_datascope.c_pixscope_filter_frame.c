#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_27__ {TYPE_5__** outputs; TYPE_2__* priv; } ;
struct TYPE_26__ {TYPE_6__* dst; } ;
struct TYPE_25__ {int width; int height; int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
struct TYPE_22__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_24__ {TYPE_1__ member_0; } ;
struct TYPE_23__ {int ww; int w; int h; int wx; int wy; int wh; int x; int y; int nb_comps; int* rgba_map; int /*<<< orphan*/ ** colors; int /*<<< orphan*/  draw; scalar_t__ is_rgb; int /*<<< orphan*/  white; int /*<<< orphan*/  black; int /*<<< orphan*/  (* pick_color ) (int /*<<< orphan*/ *,TYPE_3__*,TYPE_4__*,int,int,int*) ;int /*<<< orphan*/  dark; } ;
typedef  TYPE_2__ PixscopeContext ;
typedef  TYPE_3__ FFDrawColor ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_frame_copy (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  draw_text (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_blend_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ff_fill_rectangle (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 double sqrt (double) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_3__*,TYPE_4__*,int,int,int*) ; 

__attribute__((used)) static int pixscope_filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx  = inlink->dst;
    PixscopeContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out = ff_get_video_buffer(outlink, in->width, in->height);
    int max[4] = { 0 }, min[4] = { INT_MAX, INT_MAX, INT_MAX, INT_MAX };
    float average[4] = { 0 };
    double rms[4] = { 0 };
    const char rgba[4] = { 'R', 'G', 'B', 'A' };
    const char yuva[4] = { 'Y', 'U', 'V', 'A' };
    int x, y, X, Y, i, w, h;
    char text[128];

    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);
    av_frame_copy(out, in);

    w = s->ww / s->w;
    h = s->ww / s->h;

    if (s->wx >= 0) {
        X = (in->width - s->ww) * s->wx;
    } else {
        X = (in->width - s->ww) * -s->wx;
    }
    if (s->wy >= 0) {
        Y = (in->height - s->wh) * s->wy;
    } else {
        Y = (in->height - s->wh) * -s->wy;
    }

    if (s->wx < 0) {
        if (s->x + s->w >= X && (s->x + s->w <= X + s->ww) &&
            s->y + s->h >= Y && (s->y + s->h <= Y + s->wh)) {
            X = (in->width - s->ww) * (1 + s->wx);
        }
    }

    if (s->wy < 0) {
        if (s->x + s->w >= X && (s->x + s->w <= X + s->ww) &&
            s->y + s->h >= Y && (s->y + s->h <= Y + s->wh)) {
            Y = (in->height - s->wh) * (1 + s->wy);
        }
    }

    ff_blend_rectangle(&s->draw, &s->dark, out->data, out->linesize,
                       out->width, out->height,
                       X,
                       Y,
                       s->ww,
                       s->wh);

    for (y = 0; y < s->h; y++) {
        for (x = 0; x < s->w; x++) {
            FFDrawColor color = { { 0 } };
            int value[4] = { 0 };

            s->pick_color(&s->draw, &color, in, x + s->x, y + s->y, value);
            ff_fill_rectangle(&s->draw, &color, out->data, out->linesize,
                              x * w + (s->ww - 4 - (s->w * w)) / 2 + X, y * h + 2 + Y, w, h);
            for (i = 0; i < 4; i++) {
                rms[i]     += (double)value[i] * (double)value[i];
                average[i] += value[i];
                min[i]      = FFMIN(min[i], value[i]);
                max[i]      = FFMAX(max[i], value[i]);
            }
        }
    }

    ff_blend_rectangle(&s->draw, &s->black, out->data, out->linesize,
                       out->width, out->height,
                       s->x - 2, s->y - 2, s->w + 4, 1);

    ff_blend_rectangle(&s->draw, &s->white, out->data, out->linesize,
                       out->width, out->height,
                       s->x - 1, s->y - 1, s->w + 2, 1);

    ff_blend_rectangle(&s->draw, &s->white, out->data, out->linesize,
                       out->width, out->height,
                       s->x - 1, s->y - 1, 1, s->h + 2);

    ff_blend_rectangle(&s->draw, &s->black, out->data, out->linesize,
                       out->width, out->height,
                       s->x - 2, s->y - 2, 1, s->h + 4);

    ff_blend_rectangle(&s->draw, &s->white, out->data, out->linesize,
                       out->width, out->height,
                       s->x - 1, s->y + 1 + s->h, s->w + 3, 1);

    ff_blend_rectangle(&s->draw, &s->black, out->data, out->linesize,
                       out->width, out->height,
                       s->x - 2, s->y + 2 + s->h, s->w + 4, 1);

    ff_blend_rectangle(&s->draw, &s->white, out->data, out->linesize,
                       out->width, out->height,
                       s->x + 1 + s->w, s->y - 1, 1, s->h + 2);

    ff_blend_rectangle(&s->draw, &s->black, out->data, out->linesize,
                       out->width, out->height,
                       s->x + 2 + s->w, s->y - 2, 1, s->h + 5);

    for (i = 0; i < 4; i++) {
        rms[i] /= s->w * s->h;
        rms[i]  = sqrt(rms[i]);
        average[i] /= s->w * s->h;
    }

    snprintf(text, sizeof(text), "CH   AVG    MIN    MAX    RMS\n");
    draw_text(&s->draw, out, &s->white,        X + 28, Y + s->ww + 20,           text, 0);
    for (i = 0; i < s->nb_comps; i++) {
        int c = s->rgba_map[i];

        snprintf(text, sizeof(text), "%c  %07.1f %05d %05d %07.1f\n", s->is_rgb ? rgba[i] : yuva[i], average[c], min[c], max[c], rms[c]);
        draw_text(&s->draw, out, s->colors[i], X + 28, Y + s->ww + 20 * (i + 2), text, 0);
    }

    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}