#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ remap_point; int /*<<< orphan*/  ch_map_info; int /*<<< orphan*/  out_fifo; } ;
struct TYPE_11__ {scalar_t__ allocated_samples; scalar_t__ nb_samples; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ AudioData ;
typedef  TYPE_2__ AVAudioResampleContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 scalar_t__ REMAP_OUT_COPY ; 
 scalar_t__ av_audio_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_audio_data_add_to_fifo (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ff_audio_data_copy (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int ff_audio_data_read_from_fifo (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int handle_buffered_output(AVAudioResampleContext *avr,
                                  AudioData *output, AudioData *converted)
{
    int ret;

    if (!output || av_audio_fifo_size(avr->out_fifo) > 0 ||
        (converted && output->allocated_samples < converted->nb_samples)) {
        if (converted) {
            /* if there are any samples in the output FIFO or if the
               user-supplied output buffer is not large enough for all samples,
               we add to the output FIFO */
            av_log(avr, AV_LOG_TRACE, "[FIFO] add %s to out_fifo\n", converted->name);
            ret = ff_audio_data_add_to_fifo(avr->out_fifo, converted, 0,
                                            converted->nb_samples);
            if (ret < 0)
                return ret;
        }

        /* if the user specified an output buffer, read samples from the output
           FIFO to the user output */
        if (output && output->allocated_samples > 0) {
            av_log(avr, AV_LOG_TRACE, "[FIFO] read from out_fifo to output\n");
            av_log(avr, AV_LOG_TRACE, "[end conversion]\n");
            return ff_audio_data_read_from_fifo(avr->out_fifo, output,
                                                output->allocated_samples);
        }
    } else if (converted) {
        /* copy directly to output if it is large enough or there is not any
           data in the output FIFO */
        av_log(avr, AV_LOG_TRACE, "[copy] %s to output\n", converted->name);
        output->nb_samples = 0;
        ret = ff_audio_data_copy(output, converted,
                                 avr->remap_point == REMAP_OUT_COPY ?
                                 &avr->ch_map_info : NULL);
        if (ret < 0)
            return ret;
        av_log(avr, AV_LOG_TRACE, "[end conversion]\n");
        return output->nb_samples;
    }
    av_log(avr, AV_LOG_TRACE, "[end conversion]\n");
    return 0;
}