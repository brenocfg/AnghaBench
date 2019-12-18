#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* src; } ;
struct TYPE_14__ {int pts; int pkt_pos; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int wave_nb_samples; int wave_samples; int pts; TYPE_2__* wave; int /*<<< orphan*/  frame_nb_samples; } ;
struct TYPE_12__ {int num_channels; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_11__ {TYPE_3__* priv; } ;
typedef  TYPE_3__ FliteContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* ff_get_audio_buffer (TYPE_5__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFrame *samplesref;
    FliteContext *flite = outlink->src->priv;
    int nb_samples = FFMIN(flite->wave_nb_samples, flite->frame_nb_samples);

    if (!nb_samples)
        return AVERROR_EOF;

    samplesref = ff_get_audio_buffer(outlink, nb_samples);
    if (!samplesref)
        return AVERROR(ENOMEM);

    memcpy(samplesref->data[0], flite->wave_samples,
           nb_samples * flite->wave->num_channels * 2);
    samplesref->pts = flite->pts;
    samplesref->pkt_pos = -1;
    samplesref->sample_rate = flite->wave->sample_rate;
    flite->pts += nb_samples;
    flite->wave_samples += nb_samples * flite->wave->num_channels;
    flite->wave_nb_samples -= nb_samples;

    return ff_filter_frame(outlink, samplesref);
}