#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_17__ {int xoff; int yoff; TYPE_5__* out; TYPE_5__* in; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_22__ {TYPE_6__** inputs; TYPE_6__** outputs; TYPE_4__* priv; } ;
struct TYPE_21__ {int const w; int const h; } ;
struct TYPE_20__ {int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {int chars; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  draw; int /*<<< orphan*/  (* reverse_color ) (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ;int /*<<< orphan*/  (* pick_color ) (int /*<<< orphan*/ *,TYPE_3__*,TYPE_5__*,scalar_t__,scalar_t__,int*) ;int /*<<< orphan*/  nb_comps; int /*<<< orphan*/  nb_planes; } ;
struct TYPE_16__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {TYPE_1__ member_0; } ;
typedef  TYPE_3__ FFDrawColor ;
typedef  TYPE_4__ DatascopeContext ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterLink ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_text (int /*<<< orphan*/ *,TYPE_5__*,TYPE_3__*,int const,int const,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_fill_rectangle (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,int const,int const) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_3__*,TYPE_5__*,scalar_t__,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static int filter_color2(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    DatascopeContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFilterLink *inlink = ctx->inputs[0];
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;
    const int xoff = td->xoff;
    const int yoff = td->yoff;
    const int P = FFMAX(s->nb_planes, s->nb_comps);
    const int C = s->chars;
    const int W = (outlink->w - xoff) / (C * 10);
    const int H = (outlink->h - yoff) / (P * 12);
    const char *format[2] = {"%02X\n", "%04X\n"};
    const int slice_start = (W * jobnr) / nb_jobs;
    const int slice_end = (W * (jobnr+1)) / nb_jobs;
    int x, y, p;

    for (y = 0; y < H && (y + s->y < inlink->h); y++) {
        for (x = slice_start; x < slice_end && (x + s->x < inlink->w); x++) {
            FFDrawColor color = { { 0 } };
            FFDrawColor reverse = { { 0 } };
            int value[4] = { 0 };

            s->pick_color(&s->draw, &color, in, x + s->x, y + s->y, value);
            s->reverse_color(&s->draw, &color, &reverse);
            ff_fill_rectangle(&s->draw, &color, out->data, out->linesize,
                              xoff + x * C * 10, yoff + y * P * 12, C * 10, P * 12);

            for (p = 0; p < P; p++) {
                char text[256];

                snprintf(text, sizeof(text), format[C>>2], value[p]);
                draw_text(&s->draw, out, &reverse, xoff + x * C * 10 + 2, yoff + y * P * 12 + p * 10 + 2, text, 0);
            }
        }
    }

    return 0;
}