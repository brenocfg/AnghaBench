#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_18__ {TYPE_4__* dst; } ;
struct TYPE_17__ {int /*<<< orphan*/  nb_samples; } ;
struct TYPE_16__ {scalar_t__ nb_outputs; scalar_t__ nb_inputs; int /*<<< orphan*/  instance; } ;
typedef  TYPE_1__ LV2Context ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  connect_ports (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* ff_get_audio_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lilv_instance_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    LV2Context *s = ctx->priv;
    AVFrame *out;

    if (!s->nb_outputs ||
        (av_frame_is_writable(in) && s->nb_inputs == s->nb_outputs)) {
        out = in;
    } else {
        out = ff_get_audio_buffer(ctx->outputs[0], in->nb_samples);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }

    connect_ports(s, in, out);

    lilv_instance_run(s->instance, in->nb_samples);

    if (out != in)
        av_frame_free(&in);

    return ff_filter_frame(ctx->outputs[0], out);
}