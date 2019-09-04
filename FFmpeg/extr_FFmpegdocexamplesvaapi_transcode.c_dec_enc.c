#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  framerate; int /*<<< orphan*/  hw_frames_ctx; } ;
struct TYPE_10__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  hw_frames_ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  codecpar; int /*<<< orphan*/  time_base; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_PIX_FMT_VAAPI ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 
 char* av_err2str (int) ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 int avcodec_open2 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int avcodec_parameters_from_context (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int avcodec_receive_frame (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avcodec_send_packet (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* avformat_new_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int avformat_write_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* decoder_ctx ; 
 int encode_write (int /*<<< orphan*/ *) ; 
 TYPE_2__* encoder_ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int initialized ; 
 int /*<<< orphan*/  ofmt_ctx ; 
 TYPE_1__* ost ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int dec_enc(AVPacket *pkt, AVCodec *enc_codec)
{
    AVFrame *frame;
    int ret = 0;

    ret = avcodec_send_packet(decoder_ctx, pkt);
    if (ret < 0) {
        fprintf(stderr, "Error during decoding. Error code: %s\n", av_err2str(ret));
        return ret;
    }

    while (ret >= 0) {
        if (!(frame = av_frame_alloc()))
            return AVERROR(ENOMEM);

        ret = avcodec_receive_frame(decoder_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            av_frame_free(&frame);
            return 0;
        } else if (ret < 0) {
            fprintf(stderr, "Error while decoding. Error code: %s\n", av_err2str(ret));
            goto fail;
        }

        if (!initialized) {
            /* we need to ref hw_frames_ctx of decoder to initialize encoder's codec.
               Only after we get a decoded frame, can we obtain its hw_frames_ctx */
            encoder_ctx->hw_frames_ctx = av_buffer_ref(decoder_ctx->hw_frames_ctx);
            if (!encoder_ctx->hw_frames_ctx) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            /* set AVCodecContext Parameters for encoder, here we keep them stay
             * the same as decoder.
             * xxx: now the sample can't handle resolution change case.
             */
            encoder_ctx->time_base = av_inv_q(decoder_ctx->framerate);
            encoder_ctx->pix_fmt   = AV_PIX_FMT_VAAPI;
            encoder_ctx->width     = decoder_ctx->width;
            encoder_ctx->height    = decoder_ctx->height;

            if ((ret = avcodec_open2(encoder_ctx, enc_codec, NULL)) < 0) {
                fprintf(stderr, "Failed to open encode codec. Error code: %s\n",
                        av_err2str(ret));
                goto fail;
            }

            if (!(ost = avformat_new_stream(ofmt_ctx, enc_codec))) {
                fprintf(stderr, "Failed to allocate stream for output format.\n");
                ret = AVERROR(ENOMEM);
                goto fail;
            }

            ost->time_base = encoder_ctx->time_base;
            ret = avcodec_parameters_from_context(ost->codecpar, encoder_ctx);
            if (ret < 0) {
                fprintf(stderr, "Failed to copy the stream parameters. "
                        "Error code: %s\n", av_err2str(ret));
                goto fail;
            }

            /* write the stream header */
            if ((ret = avformat_write_header(ofmt_ctx, NULL)) < 0) {
                fprintf(stderr, "Error while writing stream header. "
                        "Error code: %s\n", av_err2str(ret));
                goto fail;
            }

            initialized = 1;
        }

        if ((ret = encode_write(frame)) < 0)
            fprintf(stderr, "Error during encoding and writing.\n");

fail:
        av_frame_free(&frame);
        if (ret < 0)
            return ret;
    }
    return 0;
}