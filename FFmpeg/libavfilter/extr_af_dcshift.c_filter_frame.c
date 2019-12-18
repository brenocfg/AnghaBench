#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  double int32_t ;
struct TYPE_18__ {TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_17__ {int channels; TYPE_4__* dst; } ;
struct TYPE_16__ {int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_15__ {double dcshift; scalar_t__ limitergain; double limiterthreshold; } ;
typedef  TYPE_1__ DCShiftContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 double INT32_MAX ; 
 double av_clipl_int32 (double) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    DCShiftContext *s = ctx->priv;
    int i, j;
    double dcshift = s->dcshift;

    if (av_frame_is_writable(in)) {
        out = in;
    } else {
        out = ff_get_audio_buffer(outlink, in->nb_samples);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }

    if (s->limitergain > 0) {
        for (i = 0; i < inlink->channels; i++) {
            const int32_t *src = (int32_t *)in->extended_data[i];
            int32_t *dst = (int32_t *)out->extended_data[i];

            for (j = 0; j < in->nb_samples; j++) {
                double d;

                d = src[j];

                if (d > s->limiterthreshold && dcshift > 0) {
                    d = (d - s->limiterthreshold) * s->limitergain /
                             (INT32_MAX - s->limiterthreshold) +
                             s->limiterthreshold + dcshift;
                } else if (d < -s->limiterthreshold && dcshift < 0) {
                    d = (d + s->limiterthreshold) * s->limitergain /
                             (INT32_MAX - s->limiterthreshold) -
                             s->limiterthreshold + dcshift;
                } else {
                    d = dcshift * INT32_MAX + d;
                }

                dst[j] = av_clipl_int32(d);
            }
        }
    } else {
        for (i = 0; i < inlink->channels; i++) {
            const int32_t *src = (int32_t *)in->extended_data[i];
            int32_t *dst = (int32_t *)out->extended_data[i];

            for (j = 0; j < in->nb_samples; j++) {
                double d = dcshift * (INT32_MAX + 1.) + src[j];

                dst[j] = av_clipl_int32(d);
            }
        }
    }

    if (out != in)
        av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}