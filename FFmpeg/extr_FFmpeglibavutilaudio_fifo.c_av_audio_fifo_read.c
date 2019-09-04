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
 scalar_t__ av_fifo_generic_read (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 

int av_audio_fifo_read(AVAudioFifo *af, void **data, int nb_samples)
{
    int i, size;

    if (nb_samples < 0)
        return AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    if (!nb_samples)
        return 0;

    size = nb_samples * af->sample_size;
    for (i = 0; i < af->nb_buffers; i++) {
        if (av_fifo_generic_read(af->buf[i], data[i], size, NULL) < 0)
            return AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    return nb_samples;
}