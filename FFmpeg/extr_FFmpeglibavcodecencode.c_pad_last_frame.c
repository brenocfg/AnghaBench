#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  channels; scalar_t__ frame_size; } ;
struct TYPE_11__ {scalar_t__ nb_samples; int /*<<< orphan*/  extended_data; int /*<<< orphan*/  channels; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_1__* av_frame_alloc () ; 
 int av_frame_copy_props (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 int av_frame_get_buffer (TYPE_1__*,int) ; 
 int av_samples_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_samples_set_silence (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pad_last_frame(AVCodecContext *s, AVFrame **dst, const AVFrame *src)
{
    AVFrame *frame = NULL;
    int ret;

    if (!(frame = av_frame_alloc()))
        return AVERROR(ENOMEM);

    frame->format         = src->format;
    frame->channel_layout = src->channel_layout;
    frame->channels       = src->channels;
    frame->nb_samples     = s->frame_size;
    ret = av_frame_get_buffer(frame, 32);
    if (ret < 0)
        goto fail;

    ret = av_frame_copy_props(frame, src);
    if (ret < 0)
        goto fail;

    if ((ret = av_samples_copy(frame->extended_data, src->extended_data, 0, 0,
                               src->nb_samples, s->channels, s->sample_fmt)) < 0)
        goto fail;
    if ((ret = av_samples_set_silence(frame->extended_data, src->nb_samples,
                                      frame->nb_samples - src->nb_samples,
                                      s->channels, s->sample_fmt)) < 0)
        goto fail;

    *dst = frame;

    return 0;

fail:
    av_frame_free(&frame);
    return ret;
}