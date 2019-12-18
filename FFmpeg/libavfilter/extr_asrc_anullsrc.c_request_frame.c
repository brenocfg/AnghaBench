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
struct TYPE_14__ {scalar_t__ nb_samples; int /*<<< orphan*/  pts; int /*<<< orphan*/  channel_layout; } ;
struct TYPE_13__ {int /*<<< orphan*/  sample_rate; TYPE_1__* src; } ;
struct TYPE_12__ {int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  pts; } ;
struct TYPE_11__ {TYPE_4__* priv; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ ANullContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int ff_filter_frame (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    int ret;
    ANullContext *null = outlink->src->priv;
    AVFrame *samplesref;

    samplesref = ff_get_audio_buffer(outlink, null->nb_samples);
    if (!samplesref)
        return AVERROR(ENOMEM);

    samplesref->pts = null->pts;
    samplesref->channel_layout = null->channel_layout;
    samplesref->sample_rate = outlink->sample_rate;

    ret = ff_filter_frame(outlink, av_frame_clone(samplesref));
    av_frame_free(&samplesref);
    if (ret < 0)
        return ret;

    null->pts += null->nb_samples;
    return ret;
}