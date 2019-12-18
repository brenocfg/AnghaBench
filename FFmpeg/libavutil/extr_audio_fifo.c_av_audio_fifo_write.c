#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sample_size; int nb_buffers; int nb_samples; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVAudioFifo ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int /*<<< orphan*/  EINVAL ; 
 int INT_MAX ; 
 int av_audio_fifo_realloc (TYPE_1__*,int) ; 
 int av_audio_fifo_size (TYPE_1__*) ; 
 int av_audio_fifo_space (TYPE_1__*) ; 
 int av_fifo_generic_write (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 

int av_audio_fifo_write(AVAudioFifo *af, void **data, int nb_samples)
{
    int i, ret, size;

    /* automatically reallocate buffers if needed */
    if (av_audio_fifo_space(af) < nb_samples) {
        int current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        if (INT_MAX / 2 - current_size < nb_samples)
            return AVERROR(EINVAL);
        /* reallocate buffers */
        if ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            return ret;
    }

    size = nb_samples * af->sample_size;
    for (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_generic_write(af->buf[i], data[i], size, NULL);
        if (ret != size)
            return AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    return nb_samples;
}