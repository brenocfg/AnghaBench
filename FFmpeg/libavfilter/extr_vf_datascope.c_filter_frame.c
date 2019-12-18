#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_19__ {int yoff; int xoff; TYPE_4__* out; TYPE_4__* in; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_23__ {TYPE_1__* internal; TYPE_5__** outputs; TYPE_3__* priv; } ;
struct TYPE_22__ {int w; int h; TYPE_6__* dst; } ;
struct TYPE_21__ {int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; int /*<<< orphan*/  pts; } ;
struct TYPE_20__ {int nb_planes; int nb_comps; int chars; int y; int x; int /*<<< orphan*/  filter; int /*<<< orphan*/  yellow; int /*<<< orphan*/  draw; int /*<<< orphan*/  gray; scalar_t__ axis; int /*<<< orphan*/  black; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ DatascopeContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  draw_text (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int,int,char*,int) ; 
 int /*<<< orphan*/  ff_fill_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_6__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx  = inlink->dst;
    DatascopeContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    ThreadData td = { 0 };
    int ymaxlen = 0;
    int xmaxlen = 0;
    AVFrame *out;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    out->pts = in->pts;

    ff_fill_rectangle(&s->draw, &s->black, out->data, out->linesize,
                      0, 0, outlink->w, outlink->h);

    if (s->axis) {
        const int P = FFMAX(s->nb_planes, s->nb_comps);
        const int C = s->chars;
        int Y = outlink->h / (P * 12);
        int X = outlink->w / (C * 10);
        char text[256] = { 0 };
        int x, y;

        snprintf(text, sizeof(text), "%d", s->y + Y);
        ymaxlen = strlen(text);
        ymaxlen *= 10;
        snprintf(text, sizeof(text), "%d", s->x + X);
        xmaxlen = strlen(text);
        xmaxlen *= 10;

        Y = (outlink->h - xmaxlen) / (P * 12);
        X = (outlink->w - ymaxlen) / (C * 10);

        for (y = 0; y < Y; y++) {
            snprintf(text, sizeof(text), "%d", s->y + y);

            ff_fill_rectangle(&s->draw, &s->gray, out->data, out->linesize,
                              0, xmaxlen + y * P * 12 + (P + 1) * P - 2, ymaxlen, 10);

            draw_text(&s->draw, out, &s->yellow, 2, xmaxlen + y * P * 12 + (P + 1) * P, text, 0);
        }

        for (x = 0; x < X; x++) {
            snprintf(text, sizeof(text), "%d", s->x + x);

            ff_fill_rectangle(&s->draw, &s->gray, out->data, out->linesize,
                              ymaxlen + x * C * 10 + 2 * C - 2, 0, 10, xmaxlen);

            draw_text(&s->draw, out, &s->yellow, ymaxlen + x * C * 10 + 2 * C, 2, text, 1);
        }
    }

    td.in = in; td.out = out, td.yoff = xmaxlen, td.xoff = ymaxlen;
    ctx->internal->execute(ctx, s->filter, &td, NULL, FFMIN(ff_filter_get_nb_threads(ctx), FFMAX(outlink->w / 20, 1)));

    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}