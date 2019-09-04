#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_16__ {int /*<<< orphan*/  codec_id; } ;
struct TYPE_15__ {TYPE_1__** streams; } ;
struct TYPE_14__ {int width; int height; int format; int /*<<< orphan*/  linesize; scalar_t__ data; } ;
struct TYPE_13__ {TYPE_4__* codecpar; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVInputFormat ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_4__ AVCodecParameters ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_find_input_format (char*) ; 
 TYPE_2__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int av_image_alloc (int /*<<< orphan*/ **,int*,int,int,int,int) ; 
 int /*<<< orphan*/  av_image_copy (int /*<<< orphan*/ **,int*,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  av_init_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int av_read_frame (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int avcodec_decode_video2 (int /*<<< orphan*/ *,TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ **) ; 
 int avcodec_open2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avcodec_parameters_to_context (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_3__**) ; 
 int avformat_find_stream_info (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avformat_open_input (TYPE_3__**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ff_load_image(uint8_t *data[4], int linesize[4],
                  int *w, int *h, enum AVPixelFormat *pix_fmt,
                  const char *filename, void *log_ctx)
{
    AVInputFormat *iformat = NULL;
    AVFormatContext *format_ctx = NULL;
    AVCodec *codec;
    AVCodecContext *codec_ctx;
    AVCodecParameters *par;
    AVFrame *frame;
    int frame_decoded, ret = 0;
    AVPacket pkt;
    AVDictionary *opt=NULL;

    av_init_packet(&pkt);

    iformat = av_find_input_format("image2pipe");
    if ((ret = avformat_open_input(&format_ctx, filename, iformat, NULL)) < 0) {
        av_log(log_ctx, AV_LOG_ERROR,
               "Failed to open input file '%s'\n", filename);
        return ret;
    }

    if ((ret = avformat_find_stream_info(format_ctx, NULL)) < 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Find stream info failed\n");
        return ret;
    }

    par = format_ctx->streams[0]->codecpar;
    codec = avcodec_find_decoder(par->codec_id);
    if (!codec) {
        av_log(log_ctx, AV_LOG_ERROR, "Failed to find codec\n");
        ret = AVERROR(EINVAL);
        goto end;
    }

    codec_ctx = avcodec_alloc_context3(codec);
    if (!codec_ctx) {
        av_log(log_ctx, AV_LOG_ERROR, "Failed to alloc video decoder context\n");
        ret = AVERROR(ENOMEM);
        goto end;
    }

    ret = avcodec_parameters_to_context(codec_ctx, par);
    if (ret < 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Failed to copy codec parameters to decoder context\n");
        goto end;
    }

    av_dict_set(&opt, "thread_type", "slice", 0);
    if ((ret = avcodec_open2(codec_ctx, codec, &opt)) < 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Failed to open codec\n");
        goto end;
    }

    if (!(frame = av_frame_alloc()) ) {
        av_log(log_ctx, AV_LOG_ERROR, "Failed to alloc frame\n");
        ret = AVERROR(ENOMEM);
        goto end;
    }

    ret = av_read_frame(format_ctx, &pkt);
    if (ret < 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Failed to read frame from file\n");
        goto end;
    }

    ret = avcodec_decode_video2(codec_ctx, frame, &frame_decoded, &pkt);
    if (ret < 0 || !frame_decoded) {
        av_log(log_ctx, AV_LOG_ERROR, "Failed to decode image from file\n");
        if (ret >= 0)
            ret = -1;
        goto end;
    }

    *w       = frame->width;
    *h       = frame->height;
    *pix_fmt = frame->format;

    if ((ret = av_image_alloc(data, linesize, *w, *h, *pix_fmt, 16)) < 0)
        goto end;
    ret = 0;

    av_image_copy(data, linesize, (const uint8_t **)frame->data, frame->linesize, *pix_fmt, *w, *h);

end:
    av_packet_unref(&pkt);
    avcodec_free_context(&codec_ctx);
    avformat_close_input(&format_ctx);
    av_frame_free(&frame);
    av_dict_free(&opt);

    if (ret < 0)
        av_log(log_ctx, AV_LOG_ERROR, "Error loading image file '%s'\n", filename);
    return ret;
}