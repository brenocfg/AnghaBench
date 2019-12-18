#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  codec_id; } ;
struct TYPE_11__ {TYPE_1__** streams; } ;
struct TYPE_10__ {TYPE_3__* codecpar; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVCodecParameters ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_DECODER_NOT_FOUND ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_find_best_stream (TYPE_2__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avcodec_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ **) ; 
 int avcodec_open2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int avcodec_parameters_to_context (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_2__**) ; 
 int avformat_find_stream_info (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int avformat_open_input (TYPE_2__**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int compute_crc_of_packets (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/ * crc_array ; 
 scalar_t__ number_of_elements ; 
 int /*<<< orphan*/ * pts_array ; 
 long read_seek_range (char const*) ; 
 scalar_t__ size_of_array ; 

__attribute__((used)) static int seek_test(const char *input_filename, const char *start, const char *end)
{
    AVCodec *codec = NULL;
    AVCodecContext *ctx= NULL;
    AVCodecParameters *origin_par = NULL;
    AVFrame *fr = NULL;
    AVFormatContext *fmt_ctx = NULL;
    int video_stream;
    int result;
    int i, j;
    long int start_ts, end_ts;

    size_of_array = 0;
    number_of_elements = 0;
    crc_array = NULL;
    pts_array = NULL;

    result = avformat_open_input(&fmt_ctx, input_filename, NULL, NULL);
    if (result < 0) {
        av_log(NULL, AV_LOG_ERROR, "Can't open file\n");
        return result;
    }

    result = avformat_find_stream_info(fmt_ctx, NULL);
    if (result < 0) {
        av_log(NULL, AV_LOG_ERROR, "Can't get stream info\n");
        goto end;
    }

    start_ts = read_seek_range(start);
    end_ts = read_seek_range(end);
    if ((start_ts < 0) || (end_ts < 0)) {
        result = -1;
        goto end;
    }

    //TODO: add ability to work with audio format
    video_stream = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (video_stream < 0) {
      av_log(NULL, AV_LOG_ERROR, "Can't find video stream in input file\n");
      result = video_stream;
      goto end;
    }

    origin_par = fmt_ctx->streams[video_stream]->codecpar;

    codec = avcodec_find_decoder(origin_par->codec_id);
    if (!codec) {
        av_log(NULL, AV_LOG_ERROR, "Can't find decoder\n");
        result = AVERROR_DECODER_NOT_FOUND;
        goto end;
    }

    ctx = avcodec_alloc_context3(codec);
    if (!ctx) {
        av_log(NULL, AV_LOG_ERROR, "Can't allocate decoder context\n");
        result = AVERROR(ENOMEM);
        goto end;
    }

    result = avcodec_parameters_to_context(ctx, origin_par);
    if (result) {
        av_log(NULL, AV_LOG_ERROR, "Can't copy decoder context\n");
        goto end;
    }

    result = avcodec_open2(ctx, codec, NULL);
    if (result < 0) {
        av_log(ctx, AV_LOG_ERROR, "Can't open decoder\n");
        goto end;
    }

    fr = av_frame_alloc();
    if (!fr) {
        av_log(NULL, AV_LOG_ERROR, "Can't allocate frame\n");
        result = AVERROR(ENOMEM);
        goto end;
    }

    result = compute_crc_of_packets(fmt_ctx, video_stream, ctx, fr, 0, 0, 1);
    if (result != 0)
        goto end;

    for (i = start_ts; i < end_ts; i += 100) {
        for (j = i + 100; j < end_ts; j += 100) {
            result = compute_crc_of_packets(fmt_ctx, video_stream, ctx, fr, i, j, 0);
            if (result != 0)
                break;
        }
    }

end:
    av_freep(&crc_array);
    av_freep(&pts_array);
    av_frame_free(&fr);
    avcodec_close(ctx);
    avformat_close_input(&fmt_ctx);
    avcodec_free_context(&ctx);
    return result;
}