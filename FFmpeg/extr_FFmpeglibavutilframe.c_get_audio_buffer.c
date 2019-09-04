#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* data; } ;
struct TYPE_8__ {int channels; int nb_extended_buf; TYPE_4__** extended_buf; TYPE_4__** extended_data; int /*<<< orphan*/ * linesize; TYPE_1__** buf; TYPE_4__** data; int /*<<< orphan*/  format; int /*<<< orphan*/  nb_samples; int /*<<< orphan*/  channel_layout; } ;
struct TYPE_7__ {TYPE_4__* data; } ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_NUM_DATA_POINTERS ; 
 int /*<<< orphan*/  CHECK_CHANNELS_CONSISTENCY (TYPE_2__*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int) ; 
 void* av_buffer_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_4__***) ; 
 int av_get_channel_layout_nb_channels (int /*<<< orphan*/ ) ; 
 void* av_mallocz_array (int,int) ; 
 int av_sample_fmt_is_planar (int /*<<< orphan*/ ) ; 
 int av_samples_get_buffer_size (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_audio_buffer(AVFrame *frame, int align)
{
    int channels;
    int planar   = av_sample_fmt_is_planar(frame->format);
    int planes;
    int ret, i;

    if (!frame->channels)
        frame->channels = av_get_channel_layout_nb_channels(frame->channel_layout);

    channels = frame->channels;
    planes = planar ? channels : 1;

    CHECK_CHANNELS_CONSISTENCY(frame);
    if (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        if (ret < 0)
            return ret;
    }

    if (planes > AV_NUM_DATA_POINTERS) {
        frame->extended_data = av_mallocz_array(planes,
                                          sizeof(*frame->extended_data));
        frame->extended_buf  = av_mallocz_array((planes - AV_NUM_DATA_POINTERS),
                                          sizeof(*frame->extended_buf));
        if (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            return AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_NUM_DATA_POINTERS;
    } else
        frame->extended_data = frame->data;

    for (i = 0; i < FFMIN(planes, AV_NUM_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(frame->linesize[0]);
        if (!frame->buf[i]) {
            av_frame_unref(frame);
            return AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] = frame->buf[i]->data;
    }
    for (i = 0; i < planes - AV_NUM_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(frame->linesize[0]);
        if (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            return AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_NUM_DATA_POINTERS] = frame->extended_buf[i]->data;
    }
    return 0;

}