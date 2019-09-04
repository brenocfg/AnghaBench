#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_3__ {int /*<<< orphan*/ * extended_data; int /*<<< orphan*/ * data; int /*<<< orphan*/  nb_samples; int /*<<< orphan*/ * linesize; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_NUM_DATA_POINTERS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_mallocz_array (int,int) ; 
 int av_sample_fmt_is_planar (int) ; 
 int av_samples_fill_arrays (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int av_samples_get_buffer_size (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 

int avcodec_fill_audio_frame(AVFrame *frame, int nb_channels,
                             enum AVSampleFormat sample_fmt, const uint8_t *buf,
                             int buf_size, int align)
{
    int ch, planar, needed_size, ret = 0;

    needed_size = av_samples_get_buffer_size(NULL, nb_channels,
                                             frame->nb_samples, sample_fmt,
                                             align);
    if (buf_size < needed_size)
        return AVERROR(EINVAL);

    planar = av_sample_fmt_is_planar(sample_fmt);
    if (planar && nb_channels > AV_NUM_DATA_POINTERS) {
        if (!(frame->extended_data = av_mallocz_array(nb_channels,
                                                sizeof(*frame->extended_data))))
            return AVERROR(ENOMEM);
    } else {
        frame->extended_data = frame->data;
    }

    if ((ret = av_samples_fill_arrays(frame->extended_data, &frame->linesize[0],
                                      (uint8_t *)(intptr_t)buf, nb_channels, frame->nb_samples,
                                      sample_fmt, align)) < 0) {
        if (frame->extended_data != frame->data)
            av_freep(&frame->extended_data);
        return ret;
    }
    if (frame->extended_data != frame->data) {
        for (ch = 0; ch < AV_NUM_DATA_POINTERS; ch++)
            frame->data[ch] = frame->extended_data[ch];
    }

    return ret;
}