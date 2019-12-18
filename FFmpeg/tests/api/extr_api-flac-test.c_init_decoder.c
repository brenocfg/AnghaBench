#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* int64_t ;
struct TYPE_6__ {void* channel_layout; void* request_channel_layout; int /*<<< orphan*/  request_sample_fmt; } ;
typedef  TYPE_1__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int avcodec_open2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_decoder(AVCodec *dec, AVCodecContext **dec_ctx,
                        int64_t ch_layout)
{
    AVCodecContext *ctx;
    int result;

    ctx = avcodec_alloc_context3(dec);
    if (!ctx) {
        av_log(NULL, AV_LOG_ERROR , "Can't allocate decoder context\n");
        return AVERROR(ENOMEM);
    }

    ctx->request_sample_fmt = AV_SAMPLE_FMT_S16;
    /* XXX: FLAC ignores it for some reason */
    ctx->request_channel_layout = ch_layout;
    ctx->channel_layout = ch_layout;

    result = avcodec_open2(ctx, dec, NULL);
    if (result < 0) {
        av_log(ctx, AV_LOG_ERROR, "Can't open decoder\n");
        return result;
    }

    *dec_ctx = ctx;
    return 0;
}