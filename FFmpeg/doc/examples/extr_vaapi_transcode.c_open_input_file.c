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
struct TYPE_12__ {int /*<<< orphan*/  get_format; int /*<<< orphan*/  hw_device_ctx; } ;
struct TYPE_11__ {TYPE_1__** streams; } ;
struct TYPE_10__ {int /*<<< orphan*/  codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 
 char* av_err2str (int) ; 
 int av_find_best_stream (TYPE_2__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 TYPE_3__* avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int avcodec_open2 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int avcodec_parameters_to_context (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int avformat_find_stream_info (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int avformat_open_input (TYPE_2__**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* decoder_ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_vaapi_format ; 
 int /*<<< orphan*/  hw_device_ctx ; 
 TYPE_2__* ifmt_ctx ; 
 int /*<<< orphan*/  stderr ; 
 size_t video_stream ; 

__attribute__((used)) static int open_input_file(const char *filename)
{
    int ret;
    AVCodec *decoder = NULL;
    AVStream *video = NULL;

    if ((ret = avformat_open_input(&ifmt_ctx, filename, NULL, NULL)) < 0) {
        fprintf(stderr, "Cannot open input file '%s', Error code: %s\n",
                filename, av_err2str(ret));
        return ret;
    }

    if ((ret = avformat_find_stream_info(ifmt_ctx, NULL)) < 0) {
        fprintf(stderr, "Cannot find input stream information. Error code: %s\n",
                av_err2str(ret));
        return ret;
    }

    ret = av_find_best_stream(ifmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, &decoder, 0);
    if (ret < 0) {
        fprintf(stderr, "Cannot find a video stream in the input file. "
                "Error code: %s\n", av_err2str(ret));
        return ret;
    }
    video_stream = ret;

    if (!(decoder_ctx = avcodec_alloc_context3(decoder)))
        return AVERROR(ENOMEM);

    video = ifmt_ctx->streams[video_stream];
    if ((ret = avcodec_parameters_to_context(decoder_ctx, video->codecpar)) < 0) {
        fprintf(stderr, "avcodec_parameters_to_context error. Error code: %s\n",
                av_err2str(ret));
        return ret;
    }

    decoder_ctx->hw_device_ctx = av_buffer_ref(hw_device_ctx);
    if (!decoder_ctx->hw_device_ctx) {
        fprintf(stderr, "A hardware device reference create failed.\n");
        return AVERROR(ENOMEM);
    }
    decoder_ctx->get_format    = get_vaapi_format;

    if ((ret = avcodec_open2(decoder_ctx, decoder, NULL)) < 0)
        fprintf(stderr, "Failed to open codec for decoding. Error code: %s\n",
                av_err2str(ret));

    return ret;
}