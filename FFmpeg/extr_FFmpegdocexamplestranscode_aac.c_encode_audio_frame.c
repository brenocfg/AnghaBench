#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nb_samples; int /*<<< orphan*/  pts; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_1__ AVFrame ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EAGAIN ; 
 char* av_err2str (int) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int av_write_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int avcodec_receive_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int avcodec_send_frame (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  init_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pts ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int encode_audio_frame(AVFrame *frame,
                              AVFormatContext *output_format_context,
                              AVCodecContext *output_codec_context,
                              int *data_present)
{
    /* Packet used for temporary storage. */
    AVPacket output_packet;
    int error;
    init_packet(&output_packet);

    /* Set a timestamp based on the sample rate for the container. */
    if (frame) {
        frame->pts = pts;
        pts += frame->nb_samples;
    }

    /* Send the audio frame stored in the temporary packet to the encoder.
     * The output audio stream encoder is used to do this. */
    error = avcodec_send_frame(output_codec_context, frame);
    /* The encoder signals that it has nothing more to encode. */
    if (error == AVERROR_EOF) {
        error = 0;
        goto cleanup;
    } else if (error < 0) {
        fprintf(stderr, "Could not send packet for encoding (error '%s')\n",
                av_err2str(error));
        return error;
    }

    /* Receive one encoded frame from the encoder. */
    error = avcodec_receive_packet(output_codec_context, &output_packet);
    /* If the encoder asks for more data to be able to provide an
     * encoded frame, return indicating that no data is present. */
    if (error == AVERROR(EAGAIN)) {
        error = 0;
        goto cleanup;
    /* If the last frame has been encoded, stop encoding. */
    } else if (error == AVERROR_EOF) {
        error = 0;
        goto cleanup;
    } else if (error < 0) {
        fprintf(stderr, "Could not encode frame (error '%s')\n",
                av_err2str(error));
        goto cleanup;
    /* Default case: Return encoded data. */
    } else {
        *data_present = 1;
    }

    /* Write one audio frame from the temporary packet to the output file. */
    if (*data_present &&
        (error = av_write_frame(output_format_context, &output_packet)) < 0) {
        fprintf(stderr, "Could not write frame (error '%s')\n",
                av_err2str(error));
        goto cleanup;
    }

cleanup:
    av_packet_unref(&output_packet);
    return error;
}