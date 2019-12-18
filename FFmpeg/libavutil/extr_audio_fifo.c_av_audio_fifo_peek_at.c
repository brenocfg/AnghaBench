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
struct TYPE_3__ {int nb_samples; int sample_size; int nb_buffers; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVAudioFifo ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int /*<<< orphan*/  EINVAL ; 
 int FFMIN (int,int) ; 
 int av_fifo_generic_peek_at (int /*<<< orphan*/ ,void*,int,int,int /*<<< orphan*/ *) ; 

int av_audio_fifo_peek_at(AVAudioFifo *af, void **data, int nb_samples, int offset)
{
    int i, ret, size;

    if (offset < 0 || offset >= af->nb_samples)
        return AVERROR(EINVAL);
    if (nb_samples < 0)
        return AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    if (!nb_samples)
        return 0;
    if (offset > af->nb_samples - nb_samples)
        return AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    for (i = 0; i < af->nb_buffers; i++) {
        if ((ret = av_fifo_generic_peek_at(af->buf[i], data[i], offset, size, NULL)) < 0)
            return AVERROR_BUG;
    }

    return nb_samples;
}