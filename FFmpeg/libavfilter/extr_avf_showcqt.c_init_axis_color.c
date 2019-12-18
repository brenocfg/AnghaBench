#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int** data; int* linesize; } ;
struct TYPE_5__ {double basefreq; double endfreq; int cqt_len; double* freq; double timeclamp; int /*<<< orphan*/  ctx; int /*<<< orphan*/  fontcolor; } ;
typedef  TYPE_1__ ShowCQTContext ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVExpr ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ BASEFREQ ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ ENDFREQ ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_expr_eval (int /*<<< orphan*/ *,double*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_expr_free (int /*<<< orphan*/ *) ; 
 int av_expr_parse (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const**,char const**,double (*) (void*,double),int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (double**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  b_func ; 
 double* create_freq_table (double,double,int) ; 
 int /*<<< orphan*/  g_func ; 
 int /*<<< orphan*/  midi ; 
 int /*<<< orphan*/  r_func ; 

__attribute__((used)) static int init_axis_color(ShowCQTContext *s, AVFrame *tmp, int half)
{
    const char *var_names[] = { "timeclamp", "tc", "frequency", "freq", "f", NULL };
    const char *func_names[] = { "midi", "r", "g", "b", NULL };
    double (*funcs[])(void *, double) = { midi, r_func, g_func, b_func };
    AVExpr *expr = NULL;
    double *freq = NULL;
    int x, xs, y, ret;
    int width = half ? 1920/2 : 1920, height = half ? 16 : 32;
    int step = half ? 2 : 1;

    if (s->basefreq != (double) BASEFREQ || s->endfreq != (double) ENDFREQ) {
        av_log(s->ctx, AV_LOG_WARNING, "font axis rendering is not implemented in non-default frequency range,"
               " please use axisfile option instead.\n");
        return AVERROR(EINVAL);
    }

    if (s->cqt_len == 1920)
        freq = s->freq;
    else if (!(freq = create_freq_table(s->basefreq, s->endfreq, 1920)))
        return AVERROR(ENOMEM);

    if ((ret = av_expr_parse(&expr, s->fontcolor, var_names, func_names, funcs, NULL, NULL, 0, s->ctx)) < 0) {
        if (freq != s->freq)
            av_freep(&freq);
        return ret;
    }

    for (x = 0, xs = 0; x < width; x++, xs += step) {
        double vars[] = { s->timeclamp, s->timeclamp, freq[xs], freq[xs], freq[xs] };
        int color = (int) av_expr_eval(expr, vars, NULL);
        uint8_t r = (color >> 16) & 0xFF, g = (color >> 8) & 0xFF, b = color & 0xFF;
        uint8_t *data = tmp->data[0];
        int linesize = tmp->linesize[0];
        for (y = 0; y < height; y++) {
            data[linesize * y + 4 * x] = r;
            data[linesize * y + 4 * x + 1] = g;
            data[linesize * y + 4 * x + 2] = b;
        }
    }

    av_expr_free(expr);
    if (freq != s->freq)
        av_freep(&freq);
    return 0;
}