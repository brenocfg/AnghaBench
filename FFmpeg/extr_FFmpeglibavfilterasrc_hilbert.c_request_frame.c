#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* priv; } ;
struct TYPE_12__ {TYPE_4__* src; } ;
struct TYPE_11__ {scalar_t__ pts; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {scalar_t__ pts; scalar_t__ taps; scalar_t__ nb_taps; int /*<<< orphan*/  nb_samples; } ;
typedef  TYPE_1__ HilbertContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    HilbertContext *s = ctx->priv;
    AVFrame *frame;
    int nb_samples;

    nb_samples = FFMIN(s->nb_samples, s->nb_taps - s->pts);
    if (!nb_samples)
        return AVERROR_EOF;

    if (!(frame = ff_get_audio_buffer(outlink, nb_samples)))
        return AVERROR(ENOMEM);

    memcpy(frame->data[0], s->taps + s->pts, nb_samples * sizeof(float));

    frame->pts = s->pts;
    s->pts    += nb_samples;
    return ff_filter_frame(outlink, frame);
}