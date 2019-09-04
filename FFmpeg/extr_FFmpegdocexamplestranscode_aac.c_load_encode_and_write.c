#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  frame_size; } ;
struct TYPE_9__ {scalar_t__ data; } ;
typedef  TYPE_1__ AVFrame ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_2__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVAudioFifo ;

/* Variables and functions */
 int AVERROR_EXIT ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int const av_audio_fifo_read (int /*<<< orphan*/ *,void**,int const) ; 
 int /*<<< orphan*/  av_audio_fifo_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 scalar_t__ encode_audio_frame (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ init_output_frame (TYPE_1__**,TYPE_2__*,int const) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int load_encode_and_write(AVAudioFifo *fifo,
                                 AVFormatContext *output_format_context,
                                 AVCodecContext *output_codec_context)
{
    /* Temporary storage of the output samples of the frame written to the file. */
    AVFrame *output_frame;
    /* Use the maximum number of possible samples per frame.
     * If there is less than the maximum possible frame size in the FIFO
     * buffer use this number. Otherwise, use the maximum possible frame size. */
    const int frame_size = FFMIN(av_audio_fifo_size(fifo),
                                 output_codec_context->frame_size);
    int data_written;

    /* Initialize temporary storage for one output frame. */
    if (init_output_frame(&output_frame, output_codec_context, frame_size))
        return AVERROR_EXIT;

    /* Read as many samples from the FIFO buffer as required to fill the frame.
     * The samples are stored in the frame temporarily. */
    if (av_audio_fifo_read(fifo, (void **)output_frame->data, frame_size) < frame_size) {
        fprintf(stderr, "Could not read data from FIFO\n");
        av_frame_free(&output_frame);
        return AVERROR_EXIT;
    }

    /* Encode one frame worth of audio samples. */
    if (encode_audio_frame(output_frame, output_format_context,
                           output_codec_context, &data_written)) {
        av_frame_free(&output_frame);
        return AVERROR_EXIT;
    }
    av_frame_free(&output_frame);
    return 0;
}