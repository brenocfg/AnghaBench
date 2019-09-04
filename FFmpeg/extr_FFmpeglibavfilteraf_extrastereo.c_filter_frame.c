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
struct TYPE_18__ {TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_17__ {TYPE_4__* dst; } ;
struct TYPE_16__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_15__ {float mult; scalar_t__ clip; } ;
typedef  TYPE_1__ ExtraStereoContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 float av_clipf (float,int,int) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    ExtraStereoContext *s = ctx->priv;
    const float *src = (const float *)in->data[0];
    const float mult = s->mult;
    AVFrame *out;
    float *dst;
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
    dst = (float *)out->data[0];

    for (n = 0; n < in->nb_samples; n++) {
        float average, left, right;

        left    = src[n * 2    ];
        right   = src[n * 2 + 1];
        average = (left + right) / 2.;
        left    = average + mult * (left  - average);
        right   = average + mult * (right - average);

        if (s->clip) {
            left  = av_clipf(left,  -1, 1);
            right = av_clipf(right, -1, 1);
        }

        dst[n * 2    ] = left;
        dst[n * 2 + 1] = right;
    }

    if (out != in)
        av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}