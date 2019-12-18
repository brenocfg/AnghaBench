#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int8_t ;
struct TYPE_14__ {int* data; } ;
struct TYPE_13__ {scalar_t__ is_disabled; TYPE_1__* priv; TYPE_2__** outputs; } ;
struct TYPE_12__ {TYPE_3__* dst; } ;
struct TYPE_11__ {int h; int qstride; int* lut; int /*<<< orphan*/  qp_expr_str; scalar_t__ evaluate_per_mb; } ;
typedef  TYPE_1__ QPContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;
typedef  TYPE_4__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t const NAN ; 
 TYPE_4__* av_buffer_alloc (int) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_4__**) ; 
 int av_expr_parse_and_eval (double*,int /*<<< orphan*/ ,char const**,double*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * av_frame_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 size_t* av_frame_get_qp_table (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  av_frame_set_qp_table (int /*<<< orphan*/ *,TYPE_4__*,int,int) ; 
 int ff_filter_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int lrintf (double) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    QPContext *s = ctx->priv;
    AVBufferRef *out_qp_table_buf;
    AVFrame *out = NULL;
    const int8_t *in_qp_table;
    int type, stride, ret;

    if (!s->qp_expr_str || ctx->is_disabled)
        return ff_filter_frame(outlink, in);

    out_qp_table_buf = av_buffer_alloc(s->h * s->qstride);
    if (!out_qp_table_buf) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    out = av_frame_clone(in);
    if (!out) {
        av_buffer_unref(&out_qp_table_buf);
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    in_qp_table = av_frame_get_qp_table(in, &stride, &type);
    av_frame_set_qp_table(out, out_qp_table_buf, s->qstride, type);


    if (s->evaluate_per_mb) {
        int y, x;

        for (y = 0; y < s->h; y++)
            for (x = 0; x < s->qstride; x++) {
                int qp = in_qp_table ? in_qp_table[x + stride * y] : NAN;
                double var_values[] = { !!in_qp_table, qp, x, y, s->qstride, s->h, 0};
                static const char *var_names[] = { "known", "qp", "x", "y", "w", "h", NULL };
                double temp_val;

                ret = av_expr_parse_and_eval(&temp_val, s->qp_expr_str,
                                            var_names, var_values,
                                            NULL, NULL, NULL, NULL, 0, 0, ctx);
                if (ret < 0)
                    goto fail;
                out_qp_table_buf->data[x + s->qstride * y] = lrintf(temp_val);
            }
    } else if (in_qp_table) {
        int y, x;

        for (y = 0; y < s->h; y++)
            for (x = 0; x < s->qstride; x++)
                out_qp_table_buf->data[x + s->qstride * y] = s->lut[129 +
                    ((int8_t)in_qp_table[x + stride * y])];
    } else {
        int y, x, qp = s->lut[0];

        for (y = 0; y < s->h; y++)
            for (x = 0; x < s->qstride; x++)
                out_qp_table_buf->data[x + s->qstride * y] = qp;
    }

    ret = ff_filter_frame(outlink, out);
    out = NULL;
fail:
    av_frame_free(&in);
    av_frame_free(&out);
    return ret;
}