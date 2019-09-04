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
struct TYPE_14__ {TYPE_1__* priv; TYPE_3__** inputs; } ;
struct TYPE_13__ {int channels; int /*<<< orphan*/  sample_rate; TYPE_4__* src; } ;
struct TYPE_12__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_11__ {scalar_t__ frame_type; int buf_size; int prev_nb_samples; double* buf; int limiter_buf_size; int buf_index; } ;
typedef  TYPE_1__ LoudNormContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FINAL_FRAME ; 
 scalar_t__ INNER_FRAME ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int) ; 
 int ff_request_frame (TYPE_3__*) ; 
 int filter_frame (TYPE_3__*,TYPE_2__*) ; 
 int frame_size (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    int ret;
    AVFilterContext *ctx = outlink->src;
    AVFilterLink *inlink = ctx->inputs[0];
    LoudNormContext *s = ctx->priv;

    ret = ff_request_frame(inlink);
    if (ret == AVERROR_EOF && s->frame_type == INNER_FRAME) {
        double *src;
        double *buf;
        int nb_samples, n, c, offset;
        AVFrame *frame;

        nb_samples  = (s->buf_size / inlink->channels) - s->prev_nb_samples;
        nb_samples -= (frame_size(inlink->sample_rate, 100) - s->prev_nb_samples);

        frame = ff_get_audio_buffer(outlink, nb_samples);
        if (!frame)
            return AVERROR(ENOMEM);
        frame->nb_samples = nb_samples;

        buf = s->buf;
        src = (double *)frame->data[0];

        offset  = ((s->limiter_buf_size / inlink->channels) - s->prev_nb_samples) * inlink->channels;
        offset -= (frame_size(inlink->sample_rate, 100) - s->prev_nb_samples) * inlink->channels;
        s->buf_index = s->buf_index - offset < 0 ? s->buf_index - offset + s->buf_size : s->buf_index - offset;

        for (n = 0; n < nb_samples; n++) {
            for (c = 0; c < inlink->channels; c++) {
                src[c] = buf[s->buf_index + c];
            }
            src += inlink->channels;
            s->buf_index += inlink->channels;
            if (s->buf_index >= s->buf_size)
                s->buf_index -= s->buf_size;
        }

        s->frame_type = FINAL_FRAME;
        ret = filter_frame(inlink, frame);
    }
    return ret;
}