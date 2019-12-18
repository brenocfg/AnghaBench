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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {int sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  sample_fmt; } ;
typedef  TYPE_1__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int NAME_BUFF_SIZE ; 
 int /*<<< orphan*/  av_get_channel_layout_string (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int avcodec_open2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_encoder(AVCodec *enc, AVCodecContext **enc_ctx,
                        int64_t ch_layout, int sample_rate)
{
    AVCodecContext *ctx;
    int result;
    char name_buff[NAME_BUFF_SIZE];

    av_get_channel_layout_string(name_buff, NAME_BUFF_SIZE, 0, ch_layout);
    av_log(NULL, AV_LOG_INFO, "channel layout: %s, sample rate: %i\n", name_buff, sample_rate);

    ctx = avcodec_alloc_context3(enc);
    if (!ctx) {
        av_log(NULL, AV_LOG_ERROR, "Can't allocate encoder context\n");
        return AVERROR(ENOMEM);
    }

    ctx->sample_fmt = AV_SAMPLE_FMT_S16;
    ctx->sample_rate = sample_rate;
    ctx->channel_layout = ch_layout;

    result = avcodec_open2(ctx, enc, NULL);
    if (result < 0) {
        av_log(ctx, AV_LOG_ERROR, "Can't open encoder\n");
        return result;
    }

    *enc_ctx = ctx;
    return 0;
}