#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_5__ {int channels; int sample_fmt; int sample_size; int nb_buffers; int allocated_samples; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVAudioFifo ;

/* Variables and functions */
 int /*<<< orphan*/  av_audio_fifo_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_fifo_alloc (int) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/ * av_mallocz_array (int,int) ; 
 scalar_t__ av_sample_fmt_is_planar (int) ; 
 scalar_t__ av_samples_get_buffer_size (int*,int,int,int,int) ; 

AVAudioFifo *av_audio_fifo_alloc(enum AVSampleFormat sample_fmt, int channels,
                                 int nb_samples)
{
    AVAudioFifo *af;
    int buf_size, i;

    /* get channel buffer size (also validates parameters) */
    if (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        return NULL;

    af = av_mallocz(sizeof(*af));
    if (!af)
        return NULL;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_mallocz_array(af->nb_buffers, sizeof(*af->buf));
    if (!af->buf)
        goto error;

    for (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc(buf_size);
        if (!af->buf[i])
            goto error;
    }
    af->allocated_samples = nb_samples;

    return af;

error:
    av_audio_fifo_free(af);
    return NULL;
}