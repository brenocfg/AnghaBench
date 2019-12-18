#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int nb_samples_pch; scalar_t__* data_planes; } ;
typedef  TYPE_1__ TestStruct ;
struct TYPE_7__ {int sample_size; int nb_buffers; } ;
typedef  TYPE_2__ AVAudioFifo ;

/* Variables and functions */
 int MAX_CHANNELS ; 
 int av_audio_fifo_write (TYPE_2__*,void**,int) ; 

__attribute__((used)) static int write_samples_to_audio_fifo(AVAudioFifo* afifo, const TestStruct *test_sample,
                                       int nb_samples, int offset)
{
    int offset_size, i;
    void *data_planes[MAX_CHANNELS];

    if(nb_samples > test_sample->nb_samples_pch - offset){
        return 0;
    }
    if(offset >= test_sample->nb_samples_pch){
        return 0;
    }
    offset_size  = offset * afifo->sample_size;

    for (i = 0; i < afifo->nb_buffers ; ++i){
        data_planes[i] = (uint8_t*)test_sample->data_planes[i] + offset_size;
    }

    return av_audio_fifo_write(afifo, data_planes, nb_samples);
}