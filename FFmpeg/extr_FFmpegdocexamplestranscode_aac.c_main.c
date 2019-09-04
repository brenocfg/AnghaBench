#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int frame_size; } ;
struct TYPE_23__ {int /*<<< orphan*/  pb; } ;
typedef  int /*<<< orphan*/  SwrContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVAudioFifo ;

/* Variables and functions */
 int AVERROR_EXIT ; 
 int /*<<< orphan*/  av_audio_fifo_free (int /*<<< orphan*/ *) ; 
 int const av_audio_fifo_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avcodec_free_context (TYPE_2__**) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_1__**) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_1__*) ; 
 int /*<<< orphan*/  avio_closep (int /*<<< orphan*/ *) ; 
 scalar_t__ encode_audio_frame (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ init_fifo (int /*<<< orphan*/ **,TYPE_2__*) ; 
 scalar_t__ init_resampler (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ **) ; 
 scalar_t__ load_encode_and_write (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ open_input_file (char*,TYPE_1__**,TYPE_2__**) ; 
 scalar_t__ open_output_file (char*,TYPE_2__*,TYPE_1__**,TYPE_2__**) ; 
 scalar_t__ read_decode_convert_and_store (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  swr_free (int /*<<< orphan*/ **) ; 
 scalar_t__ write_output_file_header (TYPE_1__*) ; 
 scalar_t__ write_output_file_trailer (TYPE_1__*) ; 

int main(int argc, char **argv)
{
    AVFormatContext *input_format_context = NULL, *output_format_context = NULL;
    AVCodecContext *input_codec_context = NULL, *output_codec_context = NULL;
    SwrContext *resample_context = NULL;
    AVAudioFifo *fifo = NULL;
    int ret = AVERROR_EXIT;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    /* Open the input file for reading. */
    if (open_input_file(argv[1], &input_format_context,
                        &input_codec_context))
        goto cleanup;
    /* Open the output file for writing. */
    if (open_output_file(argv[2], input_codec_context,
                         &output_format_context, &output_codec_context))
        goto cleanup;
    /* Initialize the resampler to be able to convert audio sample formats. */
    if (init_resampler(input_codec_context, output_codec_context,
                       &resample_context))
        goto cleanup;
    /* Initialize the FIFO buffer to store audio samples to be encoded. */
    if (init_fifo(&fifo, output_codec_context))
        goto cleanup;
    /* Write the header of the output file container. */
    if (write_output_file_header(output_format_context))
        goto cleanup;

    /* Loop as long as we have input samples to read or output samples
     * to write; abort as soon as we have neither. */
    while (1) {
        /* Use the encoder's desired frame size for processing. */
        const int output_frame_size = output_codec_context->frame_size;
        int finished                = 0;

        /* Make sure that there is one frame worth of samples in the FIFO
         * buffer so that the encoder can do its work.
         * Since the decoder's and the encoder's frame size may differ, we
         * need to FIFO buffer to store as many frames worth of input samples
         * that they make up at least one frame worth of output samples. */
        while (av_audio_fifo_size(fifo) < output_frame_size) {
            /* Decode one frame worth of audio samples, convert it to the
             * output sample format and put it into the FIFO buffer. */
            if (read_decode_convert_and_store(fifo, input_format_context,
                                              input_codec_context,
                                              output_codec_context,
                                              resample_context, &finished))
                goto cleanup;

            /* If we are at the end of the input file, we continue
             * encoding the remaining audio samples to the output file. */
            if (finished)
                break;
        }

        /* If we have enough samples for the encoder, we encode them.
         * At the end of the file, we pass the remaining samples to
         * the encoder. */
        while (av_audio_fifo_size(fifo) >= output_frame_size ||
               (finished && av_audio_fifo_size(fifo) > 0))
            /* Take one frame worth of audio samples from the FIFO buffer,
             * encode it and write it to the output file. */
            if (load_encode_and_write(fifo, output_format_context,
                                      output_codec_context))
                goto cleanup;

        /* If we are at the end of the input file and have encoded
         * all remaining samples, we can exit this loop and finish. */
        if (finished) {
            int data_written;
            /* Flush the encoder as it may have delayed frames. */
            do {
                data_written = 0;
                if (encode_audio_frame(NULL, output_format_context,
                                       output_codec_context, &data_written))
                    goto cleanup;
            } while (data_written);
            break;
        }
    }

    /* Write the trailer of the output file container. */
    if (write_output_file_trailer(output_format_context))
        goto cleanup;
    ret = 0;

cleanup:
    if (fifo)
        av_audio_fifo_free(fifo);
    swr_free(&resample_context);
    if (output_codec_context)
        avcodec_free_context(&output_codec_context);
    if (output_format_context) {
        avio_closep(&output_format_context->pb);
        avformat_free_context(output_format_context);
    }
    if (input_codec_context)
        avcodec_free_context(&input_codec_context);
    if (input_format_context)
        avformat_close_input(&input_format_context);

    return ret;
}