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
struct TYPE_5__ {int channels; int nb_buffers; int sample_size; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  nb_samples; } ;
typedef  TYPE_1__ AVAudioFifo ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int av_audio_fifo_read (TYPE_1__*,void**,int) ; 
 void* av_malloc_array (int,int) ; 
 int /*<<< orphan*/  av_sample_fmt_is_planar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_data_planes (TYPE_1__*,void**) ; 

__attribute__((used)) static int read_samples_from_audio_fifo(AVAudioFifo* afifo, void ***output, int nb_samples)
{
    int i;
    int samples        = FFMIN(nb_samples, afifo->nb_samples);
    int tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    void **data_planes = av_malloc_array(afifo->nb_buffers, sizeof(void*));
    if (!data_planes)
        ERROR("failed to allocate memory!");
    if (*output)
        free_data_planes(afifo, *output);
    *output            = data_planes;

    for (i = 0; i < afifo->nb_buffers; ++i){
        data_planes[i] = av_malloc_array(tot_elements, afifo->sample_size);
        if (!data_planes[i])
            ERROR("failed to allocate memory!");
    }

    return av_audio_fifo_read(afifo, *output, nb_samples);
}