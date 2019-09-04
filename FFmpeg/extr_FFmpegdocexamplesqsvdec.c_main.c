#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_23__ {int /*<<< orphan*/  get_format; TYPE_2__* opaque; scalar_t__ extradata_size; int /*<<< orphan*/  extradata; scalar_t__ codec_id; } ;
struct TYPE_22__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_21__ {scalar_t__ stream_index; scalar_t__ size; int /*<<< orphan*/ * data; int /*<<< orphan*/  member_0; } ;
struct TYPE_20__ {scalar_t__ index; TYPE_1__* codecpar; int /*<<< orphan*/  discard; } ;
struct TYPE_19__ {int /*<<< orphan*/  hw_device_ref; int /*<<< orphan*/ * member_0; } ;
struct TYPE_18__ {scalar_t__ codec_id; scalar_t__ extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  TYPE_2__ DecodeContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  AVDISCARD_ALL ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  AV_HWDEVICE_TYPE_QSV ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int av_hwdevice_ctx_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_mallocz (scalar_t__) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_4__*) ; 
 int av_read_frame (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_strerror (int,char*,int) ; 
 TYPE_6__* avcodec_alloc_context3 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * avcodec_find_decoder_by_name (char*) ; 
 int /*<<< orphan*/  avcodec_free_context (TYPE_6__**) ; 
 int avcodec_open2 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_5__**) ; 
 int avformat_open_input (TYPE_5__**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ *) ; 
 int avio_open (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int decode_packet (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_format ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    AVFormatContext *input_ctx = NULL;
    AVStream *video_st = NULL;
    AVCodecContext *decoder_ctx = NULL;
    const AVCodec *decoder;

    AVPacket pkt = { 0 };
    AVFrame *frame = NULL, *sw_frame = NULL;

    DecodeContext decode = { NULL };

    AVIOContext *output_ctx = NULL;

    int ret, i;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    /* open the input file */
    ret = avformat_open_input(&input_ctx, argv[1], NULL, NULL);
    if (ret < 0) {
        fprintf(stderr, "Cannot open input file '%s': ", argv[1]);
        goto finish;
    }

    /* find the first H.264 video stream */
    for (i = 0; i < input_ctx->nb_streams; i++) {
        AVStream *st = input_ctx->streams[i];

        if (st->codecpar->codec_id == AV_CODEC_ID_H264 && !video_st)
            video_st = st;
        else
            st->discard = AVDISCARD_ALL;
    }
    if (!video_st) {
        fprintf(stderr, "No H.264 video stream in the input file\n");
        goto finish;
    }

    /* open the hardware device */
    ret = av_hwdevice_ctx_create(&decode.hw_device_ref, AV_HWDEVICE_TYPE_QSV,
                                 "auto", NULL, 0);
    if (ret < 0) {
        fprintf(stderr, "Cannot open the hardware device\n");
        goto finish;
    }

    /* initialize the decoder */
    decoder = avcodec_find_decoder_by_name("h264_qsv");
    if (!decoder) {
        fprintf(stderr, "The QSV decoder is not present in libavcodec\n");
        goto finish;
    }

    decoder_ctx = avcodec_alloc_context3(decoder);
    if (!decoder_ctx) {
        ret = AVERROR(ENOMEM);
        goto finish;
    }
    decoder_ctx->codec_id = AV_CODEC_ID_H264;
    if (video_st->codecpar->extradata_size) {
        decoder_ctx->extradata = av_mallocz(video_st->codecpar->extradata_size +
                                            AV_INPUT_BUFFER_PADDING_SIZE);
        if (!decoder_ctx->extradata) {
            ret = AVERROR(ENOMEM);
            goto finish;
        }
        memcpy(decoder_ctx->extradata, video_st->codecpar->extradata,
               video_st->codecpar->extradata_size);
        decoder_ctx->extradata_size = video_st->codecpar->extradata_size;
    }

    decoder_ctx->opaque      = &decode;
    decoder_ctx->get_format  = get_format;

    ret = avcodec_open2(decoder_ctx, NULL, NULL);
    if (ret < 0) {
        fprintf(stderr, "Error opening the decoder: ");
        goto finish;
    }

    /* open the output stream */
    ret = avio_open(&output_ctx, argv[2], AVIO_FLAG_WRITE);
    if (ret < 0) {
        fprintf(stderr, "Error opening the output context: ");
        goto finish;
    }

    frame    = av_frame_alloc();
    sw_frame = av_frame_alloc();
    if (!frame || !sw_frame) {
        ret = AVERROR(ENOMEM);
        goto finish;
    }

    /* actual decoding */
    while (ret >= 0) {
        ret = av_read_frame(input_ctx, &pkt);
        if (ret < 0)
            break;

        if (pkt.stream_index == video_st->index)
            ret = decode_packet(&decode, decoder_ctx, frame, sw_frame, &pkt, output_ctx);

        av_packet_unref(&pkt);
    }

    /* flush the decoder */
    pkt.data = NULL;
    pkt.size = 0;
    ret = decode_packet(&decode, decoder_ctx, frame, sw_frame, &pkt, output_ctx);

finish:
    if (ret < 0) {
        char buf[1024];
        av_strerror(ret, buf, sizeof(buf));
        fprintf(stderr, "%s\n", buf);
    }

    avformat_close_input(&input_ctx);

    av_frame_free(&frame);
    av_frame_free(&sw_frame);

    avcodec_free_context(&decoder_ctx);

    av_buffer_unref(&decode.hw_device_ref);

    avio_close(output_ctx);

    return ret;
}