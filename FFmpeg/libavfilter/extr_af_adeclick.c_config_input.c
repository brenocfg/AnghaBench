#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ extended_data; } ;
struct TYPE_11__ {TYPE_2__* priv; } ;
struct TYPE_10__ {int sample_rate; int channels; int /*<<< orphan*/  format; TYPE_4__* dst; } ;
struct TYPE_9__ {int window_size; int w; int ar_order; int ar; int nb_burst_samples; int burst; int hop_size; int overlap; int* window_func_lut; int overlap_skip; int nb_channels; TYPE_1__* chan; TYPE_7__* in; int /*<<< orphan*/  fifo; scalar_t__ method; TYPE_7__* is; TYPE_7__* buffer; TYPE_7__* out; int /*<<< orphan*/  pts; } ;
struct TYPE_8__ {void* tmp; void* acorrelation; void* interpolated; void* index; void* click; void* detection; void* acoefficients; void* auxiliary; } ;
typedef  TYPE_1__ DeclickChannel ;
typedef  TYPE_2__ AudioDeclickContext ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
 int M_PI ; 
 int M_PI_2 ; 
 int /*<<< orphan*/  av_audio_fifo_alloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  av_audio_fifo_write (int /*<<< orphan*/ ,void**,int) ; 
 void* av_calloc (int,int) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_7__**) ; 
 void* ff_get_audio_buffer (TYPE_3__*,int) ; 
 int sin (int) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    AudioDeclickContext *s = ctx->priv;
    int i;

    s->pts = AV_NOPTS_VALUE;
    s->window_size = inlink->sample_rate * s->w / 1000.;
    if (s->window_size < 100)
        return AVERROR(EINVAL);
    s->ar_order = FFMAX(s->window_size * s->ar / 100., 1);
    s->nb_burst_samples = s->window_size * s->burst / 1000.;
    s->hop_size = s->window_size * (1. - (s->overlap / 100.));
    if (s->hop_size < 1)
        return AVERROR(EINVAL);

    s->window_func_lut = av_calloc(s->window_size, sizeof(*s->window_func_lut));
    if (!s->window_func_lut)
        return AVERROR(ENOMEM);
    for (i = 0; i < s->window_size; i++)
        s->window_func_lut[i] = sin(M_PI * i / s->window_size) *
                                (1. - (s->overlap / 100.)) * M_PI_2;

    av_frame_free(&s->in);
    av_frame_free(&s->out);
    av_frame_free(&s->buffer);
    av_frame_free(&s->is);
    s->in = ff_get_audio_buffer(inlink, s->window_size);
    s->out = ff_get_audio_buffer(inlink, s->window_size);
    s->buffer = ff_get_audio_buffer(inlink, s->window_size * 2);
    s->is = ff_get_audio_buffer(inlink, s->window_size);
    if (!s->in || !s->out || !s->buffer || !s->is)
        return AVERROR(ENOMEM);

    s->fifo = av_audio_fifo_alloc(inlink->format, inlink->channels, s->window_size);
    if (!s->fifo)
        return AVERROR(ENOMEM);
    s->overlap_skip = s->method ? (s->window_size - s->hop_size) / 2 : 0;
    if (s->overlap_skip > 0) {
        av_audio_fifo_write(s->fifo, (void **)s->in->extended_data,
                            s->overlap_skip);
    }

    s->nb_channels = inlink->channels;
    s->chan = av_calloc(inlink->channels, sizeof(*s->chan));
    if (!s->chan)
        return AVERROR(ENOMEM);

    for (i = 0; i < inlink->channels; i++) {
        DeclickChannel *c = &s->chan[i];

        c->detection = av_calloc(s->window_size, sizeof(*c->detection));
        c->auxiliary = av_calloc(s->ar_order + 1, sizeof(*c->auxiliary));
        c->acoefficients = av_calloc(s->ar_order + 1, sizeof(*c->acoefficients));
        c->acorrelation = av_calloc(s->ar_order + 1, sizeof(*c->acorrelation));
        c->tmp = av_calloc(s->ar_order, sizeof(*c->tmp));
        c->click = av_calloc(s->window_size, sizeof(*c->click));
        c->index = av_calloc(s->window_size, sizeof(*c->index));
        c->interpolated = av_calloc(s->window_size, sizeof(*c->interpolated));
        if (!c->auxiliary || !c->acoefficients || !c->detection || !c->click ||
            !c->index || !c->interpolated || !c->acorrelation || !c->tmp)
            return AVERROR(ENOMEM);
    }

    return 0;
}