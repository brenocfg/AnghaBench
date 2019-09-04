#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  samples_skipped; } ;
struct TYPE_18__ {int /*<<< orphan*/  time_base; TYPE_9__ fifo; int /*<<< orphan*/  format; int /*<<< orphan*/  channels; int /*<<< orphan*/  min_samples; } ;
struct TYPE_17__ {unsigned int nb_samples; int /*<<< orphan*/  extended_data; int /*<<< orphan*/  pts; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert1 (int /*<<< orphan*/ ) ; 
 int av_frame_copy_props (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 int /*<<< orphan*/  av_samples_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ff_framequeue_peek (TYPE_9__*,unsigned int) ; 
 unsigned int ff_framequeue_queued_frames (TYPE_9__*) ; 
 int /*<<< orphan*/  ff_framequeue_skip_samples (TYPE_9__*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* ff_framequeue_take (TYPE_9__*) ; 
 TYPE_1__* ff_get_audio_buffer (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  samples_ready (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int take_samples(AVFilterLink *link, unsigned min, unsigned max,
                        AVFrame **rframe)
{
    AVFrame *frame0, *frame, *buf;
    unsigned nb_samples, nb_frames, i, p;
    int ret;

    /* Note: this function relies on no format changes and must only be
       called with enough samples. */
    av_assert1(samples_ready(link, link->min_samples));
    frame0 = frame = ff_framequeue_peek(&link->fifo, 0);
    if (!link->fifo.samples_skipped && frame->nb_samples >= min && frame->nb_samples <= max) {
        *rframe = ff_framequeue_take(&link->fifo);
        return 0;
    }
    nb_frames = 0;
    nb_samples = 0;
    while (1) {
        if (nb_samples + frame->nb_samples > max) {
            if (nb_samples < min)
                nb_samples = max;
            break;
        }
        nb_samples += frame->nb_samples;
        nb_frames++;
        if (nb_frames == ff_framequeue_queued_frames(&link->fifo))
            break;
        frame = ff_framequeue_peek(&link->fifo, nb_frames);
    }

    buf = ff_get_audio_buffer(link, nb_samples);
    if (!buf)
        return AVERROR(ENOMEM);
    ret = av_frame_copy_props(buf, frame0);
    if (ret < 0) {
        av_frame_free(&buf);
        return ret;
    }
    buf->pts = frame0->pts;

    p = 0;
    for (i = 0; i < nb_frames; i++) {
        frame = ff_framequeue_take(&link->fifo);
        av_samples_copy(buf->extended_data, frame->extended_data, p, 0,
                        frame->nb_samples, link->channels, link->format);
        p += frame->nb_samples;
        av_frame_free(&frame);
    }
    if (p < nb_samples) {
        unsigned n = nb_samples - p;
        frame = ff_framequeue_peek(&link->fifo, 0);
        av_samples_copy(buf->extended_data, frame->extended_data, p, 0, n,
                        link->channels, link->format);
        ff_framequeue_skip_samples(&link->fifo, n, link->time_base);
    }

    *rframe = buf;
    return 0;
}