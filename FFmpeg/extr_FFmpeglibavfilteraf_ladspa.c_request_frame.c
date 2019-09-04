#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_17__ {int /*<<< orphan*/ * inputs; scalar_t__ nb_inputs; TYPE_2__* priv; } ;
struct TYPE_16__ {TYPE_5__* src; } ;
struct TYPE_15__ {int /*<<< orphan*/  pts; int /*<<< orphan*/  sample_rate; scalar_t__* extended_data; } ;
struct TYPE_14__ {scalar_t__ duration; int nb_outputs; int nb_outputcontrols; scalar_t__ nb_samples; int /*<<< orphan*/  pts; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  octlv; int /*<<< orphan*/  ocmap; int /*<<< orphan*/ * handles; TYPE_1__* desc; int /*<<< orphan*/ * opmap; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* run ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* connect_port ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  LADSPA_Data ;
typedef  TYPE_2__ LADSPAContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_TIME_BASE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_rescale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* ff_get_audio_buffer (TYPE_4__*,scalar_t__) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_ctl_info (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    LADSPAContext *s = ctx->priv;
    AVFrame *out;
    int64_t t;
    int i;

    if (ctx->nb_inputs)
        return ff_request_frame(ctx->inputs[0]);

    t = av_rescale(s->pts, AV_TIME_BASE, s->sample_rate);
    if (s->duration >= 0 && t >= s->duration)
        return AVERROR_EOF;

    out = ff_get_audio_buffer(outlink, s->nb_samples);
    if (!out)
        return AVERROR(ENOMEM);

    for (i = 0; i < s->nb_outputs; i++)
        s->desc->connect_port(s->handles[0], s->opmap[i],
                (LADSPA_Data*)out->extended_data[i]);

    s->desc->run(s->handles[0], s->nb_samples);

    for (i = 0; i < s->nb_outputcontrols; i++)
        print_ctl_info(ctx, AV_LOG_INFO, s, i, s->ocmap, s->octlv, 1);

    out->sample_rate = s->sample_rate;
    out->pts         = s->pts;
    s->pts          += s->nb_samples;

    return ff_filter_frame(outlink, out);
}