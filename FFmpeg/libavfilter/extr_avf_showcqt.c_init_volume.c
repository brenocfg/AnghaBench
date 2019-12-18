#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double* sono_v_buf; int cqt_len; double* bar_v_buf; double timeclamp; double* freq; int /*<<< orphan*/  ctx; int /*<<< orphan*/  bar_v; int /*<<< orphan*/  sono_v; } ;
typedef  TYPE_1__ ShowCQTContext ;
typedef  int /*<<< orphan*/  AVExpr ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  VOLUME_MAX ; 
 int /*<<< orphan*/  a_weighting ; 
 int /*<<< orphan*/  av_expr_eval (int /*<<< orphan*/ *,double*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_expr_free (int /*<<< orphan*/ *) ; 
 int av_expr_parse (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const**,char const**,double (*) (void*,double),int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (double**) ; 
 void* av_malloc_array (int,int) ; 
 int /*<<< orphan*/  b_weighting ; 
 int /*<<< orphan*/  c_weighting ; 
 double clip_with_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,double,int) ; 

__attribute__((used)) static int init_volume(ShowCQTContext *s)
{
    const char *func_names[] = { "a_weighting", "b_weighting", "c_weighting", NULL };
    const char *sono_names[] = { "timeclamp", "tc", "frequency", "freq", "f", "bar_v", NULL };
    const char *bar_names[] = { "timeclamp", "tc", "frequency", "freq", "f", "sono_v", NULL };
    double (*funcs[])(void *, double) = { a_weighting, b_weighting, c_weighting };
    AVExpr *sono = NULL, *bar = NULL;
    int x, ret = AVERROR(ENOMEM);

    s->sono_v_buf = av_malloc_array(s->cqt_len, sizeof(*s->sono_v_buf));
    s->bar_v_buf = av_malloc_array(s->cqt_len, sizeof(*s->bar_v_buf));
    if (!s->sono_v_buf || !s->bar_v_buf)
        goto error;

    if ((ret = av_expr_parse(&sono, s->sono_v, sono_names, func_names, funcs, NULL, NULL, 0, s->ctx)) < 0)
        goto error;

    if ((ret = av_expr_parse(&bar, s->bar_v, bar_names, func_names, funcs, NULL, NULL, 0, s->ctx)) < 0)
        goto error;

    for (x = 0; x < s->cqt_len; x++) {
        double vars[] = { s->timeclamp, s->timeclamp, s->freq[x], s->freq[x], s->freq[x], 0.0 };
        double vol = clip_with_log(s->ctx, "sono_v", av_expr_eval(sono, vars, NULL), 0.0, VOLUME_MAX, 0.0, x);
        vars[5] = vol;
        vol = clip_with_log(s->ctx, "bar_v", av_expr_eval(bar, vars, NULL), 0.0, VOLUME_MAX, 0.0, x);
        s->bar_v_buf[x] = vol * vol;
        vars[5] = vol;
        vol = clip_with_log(s->ctx, "sono_v", av_expr_eval(sono, vars, NULL), 0.0, VOLUME_MAX, 0.0, x);
        s->sono_v_buf[x] = vol * vol;
    }
    av_expr_free(sono);
    av_expr_free(bar);
    return 0;

error:
    av_freep(&s->sono_v_buf);
    av_freep(&s->bar_v_buf);
    av_expr_free(sono);
    av_expr_free(bar);
    return ret;
}