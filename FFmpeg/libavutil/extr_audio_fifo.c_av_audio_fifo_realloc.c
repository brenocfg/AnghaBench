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
struct TYPE_3__ {int nb_buffers; int allocated_samples; int /*<<< orphan*/ * buf; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  channels; } ;
typedef  TYPE_1__ AVAudioFifo ;

/* Variables and functions */
 int av_fifo_realloc2 (int /*<<< orphan*/ ,int) ; 
 int av_samples_get_buffer_size (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

int av_audio_fifo_realloc(AVAudioFifo *af, int nb_samples)
{
    int i, ret, buf_size;

    if ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        return ret;

    for (i = 0; i < af->nb_buffers; i++) {
        if ((ret = av_fifo_realloc2(af->buf[i], buf_size)) < 0)
            return ret;
    }
    af->allocated_samples = nb_samples;
    return 0;
}