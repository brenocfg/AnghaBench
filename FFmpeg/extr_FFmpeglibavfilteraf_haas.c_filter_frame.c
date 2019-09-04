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
typedef  size_t uint32_t ;
struct TYPE_18__ {TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_17__ {TYPE_4__* dst; } ;
struct TYPE_16__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_15__ {double level_in; double level_out; size_t buffer_size; double* buffer; int par_m_source; size_t write_ptr; size_t const* delay; double par_side_gain; double* balance_l; double* balance_r; scalar_t__ par_middle_phase; } ;
typedef  TYPE_1__ HaasContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    HaasContext *s = ctx->priv;
    const double *src = (const double *)in->data[0];
    const double level_in = s->level_in;
    const double level_out = s->level_out;
    const uint32_t mask = s->buffer_size - 1;
    double *buffer = s->buffer;
    AVFrame *out;
    double *dst;
    int n;

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
    dst = (double *)out->data[0];

    for (n = 0; n < in->nb_samples; n++, src += 2, dst += 2) {
        double mid, side[2], side_l, side_r;
        uint32_t s0_ptr, s1_ptr;

        switch (s->par_m_source) {
        case 0: mid = src[0]; break;
        case 1: mid = src[1]; break;
        case 2: mid = (src[0] + src[1]) * 0.5; break;
        case 3: mid = (src[0] - src[1]) * 0.5; break;
        }

        mid *= level_in;

        buffer[s->write_ptr] = mid;

        s0_ptr = (s->write_ptr + s->buffer_size - s->delay[0]) & mask;
        s1_ptr = (s->write_ptr + s->buffer_size - s->delay[1]) & mask;

        if (s->par_middle_phase)
            mid = -mid;

        side[0] = buffer[s0_ptr] * s->par_side_gain;
        side[1] = buffer[s1_ptr] * s->par_side_gain;
        side_l  = side[0] * s->balance_l[0] - side[1] * s->balance_l[1];
        side_r  = side[1] * s->balance_r[1] - side[0] * s->balance_r[0];

        dst[0] = (mid + side_l) * level_out;
        dst[1] = (mid + side_r) * level_out;

        s->write_ptr = (s->write_ptr + 1) & mask;
    }

    if (out != in)
        av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}