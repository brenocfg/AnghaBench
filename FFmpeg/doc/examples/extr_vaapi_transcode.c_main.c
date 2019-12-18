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
struct TYPE_12__ {int /*<<< orphan*/  pb; } ;
struct TYPE_11__ {scalar_t__ stream_index; scalar_t__ size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_HWDEVICE_TYPE_VAAPI ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 char* av_err2str (int) ; 
 int av_hwdevice_ctx_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int av_read_frame (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_write_trailer (TYPE_2__*) ; 
 int /*<<< orphan*/  avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avcodec_find_encoder_by_name (char*) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ *) ; 
 int avformat_alloc_output_context2 (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_2__**) ; 
 int avio_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int dec_enc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decoder_ctx ; 
 int encode_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encoder_ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  hw_device_ctx ; 
 TYPE_2__* ifmt_ctx ; 
 TYPE_2__* ofmt_ctx ; 
 int open_input_file (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ video_stream ; 

int main(int argc, char **argv)
{
    int ret = 0;
    AVPacket dec_pkt;
    AVCodec *enc_codec;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input file> <encode codec> <output file>\n"
                "The output format is guessed according to the file extension.\n"
                "\n", argv[0]);
        return -1;
    }

    ret = av_hwdevice_ctx_create(&hw_device_ctx, AV_HWDEVICE_TYPE_VAAPI, NULL, NULL, 0);
    if (ret < 0) {
        fprintf(stderr, "Failed to create a VAAPI device. Error code: %s\n", av_err2str(ret));
        return -1;
    }

    if ((ret = open_input_file(argv[1])) < 0)
        goto end;

    if (!(enc_codec = avcodec_find_encoder_by_name(argv[2]))) {
        fprintf(stderr, "Could not find encoder '%s'\n", argv[2]);
        ret = -1;
        goto end;
    }

    if ((ret = (avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, argv[3]))) < 0) {
        fprintf(stderr, "Failed to deduce output format from file extension. Error code: "
                "%s\n", av_err2str(ret));
        goto end;
    }

    if (!(encoder_ctx = avcodec_alloc_context3(enc_codec))) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    ret = avio_open(&ofmt_ctx->pb, argv[3], AVIO_FLAG_WRITE);
    if (ret < 0) {
        fprintf(stderr, "Cannot open output file. "
                "Error code: %s\n", av_err2str(ret));
        goto end;
    }

    /* read all packets and only transcoding video */
    while (ret >= 0) {
        if ((ret = av_read_frame(ifmt_ctx, &dec_pkt)) < 0)
            break;

        if (video_stream == dec_pkt.stream_index)
            ret = dec_enc(&dec_pkt, enc_codec);

        av_packet_unref(&dec_pkt);
    }

    /* flush decoder */
    dec_pkt.data = NULL;
    dec_pkt.size = 0;
    ret = dec_enc(&dec_pkt, enc_codec);
    av_packet_unref(&dec_pkt);

    /* flush encoder */
    ret = encode_write(NULL);

    /* write the trailer for output stream */
    av_write_trailer(ofmt_ctx);

end:
    avformat_close_input(&ifmt_ctx);
    avformat_close_input(&ofmt_ctx);
    avcodec_free_context(&decoder_ctx);
    avcodec_free_context(&encoder_ctx);
    av_buffer_unref(&hw_device_ctx);
    return ret;
}