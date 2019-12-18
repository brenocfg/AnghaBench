#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_37__ {int /*<<< orphan*/  name; } ;
struct TYPE_36__ {int thread_count; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  draw_horiz_band; } ;
struct TYPE_35__ {int /*<<< orphan*/  codec_id; } ;
struct TYPE_34__ {TYPE_1__** streams; } ;
struct TYPE_33__ {scalar_t__ linesize; scalar_t__ data; } ;
struct TYPE_32__ {int stream_index; scalar_t__ size; int /*<<< orphan*/ * data; } ;
struct TYPE_31__ {TYPE_5__* codecpar; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVCodecParameters ;
typedef  TYPE_6__ AVCodecContext ;
typedef  TYPE_7__ AVCodec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_adler32_update (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int av_find_best_stream (TYPE_4__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int av_image_copy_to_buffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const* const*,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int av_image_get_buffer_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 scalar_t__ av_read_frame (TYPE_4__*,TYPE_2__*) ; 
 TYPE_6__* avcodec_alloc_context3 (TYPE_7__*) ; 
 int /*<<< orphan*/  avcodec_close (TYPE_6__*) ; 
 int avcodec_decode_video2 (TYPE_6__*,TYPE_3__*,int*,TYPE_2__*) ; 
 TYPE_7__* avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_free_context (TYPE_6__**) ; 
 int avcodec_open2 (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int avcodec_parameters_to_context (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_4__**) ; 
 int avformat_find_stream_info (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int avformat_open_input (TYPE_4__**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  draw_horiz_band ; 
 scalar_t__ draw_horiz_band_called ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * slice_byte_buffer ; 
 int slice_byte_buffer_size ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int video_decode(const char *input_filename)
{
    AVCodec *codec = NULL;
    AVCodecContext *ctx= NULL;
    AVCodecParameters *origin_par = NULL;
    uint8_t *byte_buffer = NULL;
    AVFrame *fr = NULL;
    AVPacket pkt;
    AVFormatContext *fmt_ctx = NULL;
    int number_of_written_bytes;
    int video_stream;
    int got_frame = 0;
    int byte_buffer_size;
    int result;
    int end_of_stream = 0;

    draw_horiz_band_called = 0;

    result = avformat_open_input(&fmt_ctx, input_filename, NULL, NULL);
    if (result < 0) {
        av_log(NULL, AV_LOG_ERROR, "Can't open file\n");
        return result;
    }

    result = avformat_find_stream_info(fmt_ctx, NULL);
    if (result < 0) {
        av_log(NULL, AV_LOG_ERROR, "Can't get stream info\n");
        return result;
    }

    video_stream = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (video_stream < 0) {
      av_log(NULL, AV_LOG_ERROR, "Can't find video stream in input file\n");
      return -1;
    }

    origin_par = fmt_ctx->streams[video_stream]->codecpar;

    codec = avcodec_find_decoder(origin_par->codec_id);
    if (!codec) {
        av_log(NULL, AV_LOG_ERROR, "Can't find decoder\n");
        return -1;
    }

    ctx = avcodec_alloc_context3(codec);
    if (!ctx) {
        av_log(NULL, AV_LOG_ERROR, "Can't allocate decoder context\n");
        return AVERROR(ENOMEM);
    }

    result = avcodec_parameters_to_context(ctx, origin_par);
    if (result) {
        av_log(NULL, AV_LOG_ERROR, "Can't copy decoder context\n");
        return result;
    }

    ctx->draw_horiz_band = draw_horiz_band;
    ctx->thread_count = 1;

    result = avcodec_open2(ctx, codec, NULL);
    if (result < 0) {
        av_log(ctx, AV_LOG_ERROR, "Can't open decoder\n");
        return result;
    }

    fr = av_frame_alloc();
    if (!fr) {
        av_log(NULL, AV_LOG_ERROR, "Can't allocate frame\n");
        return AVERROR(ENOMEM);
    }

    if (strcmp(codec->name, "flv") && strcmp(codec->name, "mpeg4") && strcmp(codec->name, "huffyuv")) {
        av_log(NULL, AV_LOG_ERROR, "Wrong codec\n");
        return -1;
    }

    byte_buffer_size = av_image_get_buffer_size(ctx->pix_fmt, ctx->width, ctx->height, 32);
    byte_buffer = av_malloc(byte_buffer_size);
    if (!byte_buffer) {
        av_log(NULL, AV_LOG_ERROR, "Can't allocate buffer\n");
        return AVERROR(ENOMEM);
    }

    slice_byte_buffer = av_malloc(byte_buffer_size);
    if (!slice_byte_buffer) {
        av_log(NULL, AV_LOG_ERROR, "Can't allocate buffer\n");
        return AVERROR(ENOMEM);
    }
    memset(slice_byte_buffer, 0, byte_buffer_size);
    slice_byte_buffer_size = byte_buffer_size;

    av_init_packet(&pkt);
    do {
        if (!end_of_stream) {
            if (av_read_frame(fmt_ctx, &pkt) < 0) {
                end_of_stream = 1;
            }
        }
        if (end_of_stream) {
            pkt.data = NULL;
            pkt.size = 0;
        }
        if (pkt.stream_index == video_stream || end_of_stream) {
            got_frame = 0;
            result = avcodec_decode_video2(ctx, fr, &got_frame, &pkt);
            if (result < 0) {
                av_log(NULL, AV_LOG_ERROR, "Error decoding frame\n");
                return result;
            }
            if (got_frame) {
                number_of_written_bytes = av_image_copy_to_buffer(byte_buffer, byte_buffer_size,
                                        (const uint8_t* const *)fr->data, (const int*) fr->linesize,
                                        ctx->pix_fmt, ctx->width, ctx->height, 1);
                if (number_of_written_bytes < 0) {
                    av_log(NULL, AV_LOG_ERROR, "Can't copy image to buffer\n");
                    return number_of_written_bytes;
                }
                if (draw_horiz_band_called == 0) {
                    av_log(NULL, AV_LOG_ERROR, "draw_horiz_band haven't been called!\n");
                    return -1;
                }
                if (av_adler32_update(0, (const uint8_t*)byte_buffer, number_of_written_bytes) !=
                    av_adler32_update(0, (const uint8_t*)slice_byte_buffer, number_of_written_bytes)) {
                    av_log(NULL, AV_LOG_ERROR, "Decoded frames with and without draw_horiz_band are not the same!\n");
                    return -1;
                }
            }
            av_packet_unref(&pkt);
            av_init_packet(&pkt);
        }
    } while (!end_of_stream || got_frame);

    av_packet_unref(&pkt);
    av_frame_free(&fr);
    avcodec_close(ctx);
    avformat_close_input(&fmt_ctx);
    avcodec_free_context(&ctx);
    av_freep(&byte_buffer);
    av_freep(&slice_byte_buffer);
    return 0;
}