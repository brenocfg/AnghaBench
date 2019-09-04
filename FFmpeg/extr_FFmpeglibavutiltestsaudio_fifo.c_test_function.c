#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  nb_samples_pch; int /*<<< orphan*/  nb_ch; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ TestStruct ;
struct TYPE_16__ {int nb_samples; } ;
typedef  TYPE_2__ AVAudioFifo ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 TYPE_2__* av_audio_fifo_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_audio_fifo_drain (TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_audio_fifo_free (TYPE_2__*) ; 
 int av_audio_fifo_peek (TYPE_2__*,void**,int) ; 
 int av_audio_fifo_peek_at (TYPE_2__*,void**,int,int) ; 
 int av_audio_fifo_size (TYPE_2__*) ; 
 int /*<<< orphan*/  free_data_planes (TYPE_2__*,void**) ; 
 int /*<<< orphan*/  print_audio_bytes (TYPE_1__ const*,void**,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_samples_from_audio_fifo (TYPE_2__*,void***,int /*<<< orphan*/ ) ; 
 int write_samples_to_audio_fifo (TYPE_2__*,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_function(const TestStruct *test_sample)
{
    int ret, i;
    void **output_data  = NULL;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    if (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    if (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    printf("written: %d\n", ret);

    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    if (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    printf("written: %d\n", ret);
    printf("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_data, test_sample->nb_samples_pch);
    if (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    printf("read: %d\n", ret);
    print_audio_bytes(test_sample, output_data, ret);
    printf("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_data, afifo->nb_samples);
    if (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    printf("peek:\n");
    print_audio_bytes(test_sample, output_data, ret);
    printf("\n");

    /* test av_audio_fifo_peek_at */
    printf("peek_at:\n");
    for (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_data, 1, i);
        if (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        printf("%d:\n", i);
        print_audio_bytes(test_sample, output_data, ret);
    }
    printf("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    if (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    if (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_data_planes(afifo, output_data);
    av_audio_fifo_free(afifo);
}