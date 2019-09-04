#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int skip_frame; int /*<<< orphan*/  codec; int /*<<< orphan*/  codec_id; } ;
struct TYPE_10__ {scalar_t__ size; int data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVDISCARD_ALL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int avcodec_decode_video2 (TYPE_2__*,int /*<<< orphan*/ *,int*,TYPE_1__*) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_is_open (TYPE_2__*) ; 
 int avcodec_open2 (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ avpriv_codec_get_cap_skip_frame_fill_param (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_decode_video_frame(AVCodecContext *codec_ctx, AVPacket *pkt, int decode)
{
    int ret = 0;
    int got_frame = 0;
    AVFrame *frame = NULL;
    int skip_frame = codec_ctx->skip_frame;

    if (!avcodec_is_open(codec_ctx)) {
        const AVCodec *codec = avcodec_find_decoder(codec_ctx->codec_id);

        ret = avcodec_open2(codec_ctx, codec, NULL);
        if (ret < 0) {
            av_log(codec_ctx, AV_LOG_ERROR, "Failed to open codec\n");
            goto end;
        }
    }

    frame = av_frame_alloc();
    if (!frame) {
        av_log(NULL, AV_LOG_ERROR, "Failed to allocate frame\n");
        goto end;
    }

    if (!decode && avpriv_codec_get_cap_skip_frame_fill_param(codec_ctx->codec)) {
        codec_ctx->skip_frame = AVDISCARD_ALL;
    }

    do {
        ret = avcodec_decode_video2(codec_ctx, frame, &got_frame, pkt);
        av_assert0(decode || (!decode && !got_frame));
        if (ret < 0)
            break;
        pkt->data += ret;
        pkt->size -= ret;

        if (got_frame) {
            break;
        }
    } while (pkt->size > 0);

end:
    codec_ctx->skip_frame = skip_frame;

    av_frame_free(&frame);
    return ret;
}