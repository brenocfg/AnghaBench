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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  nb_samples; scalar_t__ extended_data; } ;
typedef  int /*<<< orphan*/  SwrContext ;
typedef  TYPE_1__ AVFrame ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  int /*<<< orphan*/  AVAudioFifo ;

/* Variables and functions */
 int AVERROR_EXIT ; 
 scalar_t__ add_samples_to_fifo (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 scalar_t__ convert_samples (int /*<<< orphan*/  const**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ decode_audio_frame (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 scalar_t__ init_converted_samples (int /*<<< orphan*/ ***,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ init_input_frame (TYPE_1__**) ; 

__attribute__((used)) static int read_decode_convert_and_store(AVAudioFifo *fifo,
                                         AVFormatContext *input_format_context,
                                         AVCodecContext *input_codec_context,
                                         AVCodecContext *output_codec_context,
                                         SwrContext *resampler_context,
                                         int *finished)
{
    /* Temporary storage of the input samples of the frame read from the file. */
    AVFrame *input_frame = NULL;
    /* Temporary storage for the converted input samples. */
    uint8_t **converted_input_samples = NULL;
    int data_present = 0;
    int ret = AVERROR_EXIT;

    /* Initialize temporary storage for one input frame. */
    if (init_input_frame(&input_frame))
        goto cleanup;
    /* Decode one frame worth of audio samples. */
    if (decode_audio_frame(input_frame, input_format_context,
                           input_codec_context, &data_present, finished))
        goto cleanup;
    /* If we are at the end of the file and there are no more samples
     * in the decoder which are delayed, we are actually finished.
     * This must not be treated as an error. */
    if (*finished) {
        ret = 0;
        goto cleanup;
    }
    /* If there is decoded data, convert and store it. */
    if (data_present) {
        /* Initialize the temporary storage for the converted input samples. */
        if (init_converted_samples(&converted_input_samples, output_codec_context,
                                   input_frame->nb_samples))
            goto cleanup;

        /* Convert the input samples to the desired output sample format.
         * This requires a temporary storage provided by converted_input_samples. */
        if (convert_samples((const uint8_t**)input_frame->extended_data, converted_input_samples,
                            input_frame->nb_samples, resampler_context))
            goto cleanup;

        /* Add the converted input samples to the FIFO buffer for later processing. */
        if (add_samples_to_fifo(fifo, converted_input_samples,
                                input_frame->nb_samples))
            goto cleanup;
        ret = 0;
    }
    ret = 0;

cleanup:
    if (converted_input_samples) {
        av_freep(&converted_input_samples[0]);
        free(converted_input_samples);
    }
    av_frame_free(&input_frame);

    return ret;
}