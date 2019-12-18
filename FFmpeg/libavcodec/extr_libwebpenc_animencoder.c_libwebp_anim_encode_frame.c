#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_12__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  error_code; } ;
typedef  TYPE_2__ WebPPicture ;
struct TYPE_27__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ WebPData ;
struct TYPE_30__ {int pts; } ;
struct TYPE_29__ {int pts; int dts; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; } ;
struct TYPE_24__ {int /*<<< orphan*/  config; } ;
struct TYPE_25__ {int num; int den; } ;
struct TYPE_28__ {int done; int prev_frame_pts; TYPE_12__ cc; int /*<<< orphan*/  enc; TYPE_1__ time_base; struct TYPE_28__* priv_data; } ;
typedef  TYPE_4__ LibWebPAnimContext ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  VP8_ENC_ERROR_OUT_OF_MEMORY ; 
 int WebPAnimEncoderAdd (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int WebPAnimEncoderAssemble (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  WebPPictureFree (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_6__**) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_libwebp_error_to_averror (int /*<<< orphan*/ ) ; 
 int ff_libwebp_get_frame (TYPE_4__*,TYPE_12__*,TYPE_6__ const*,TYPE_6__**,TYPE_2__**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libwebp_anim_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                                     const AVFrame *frame, int *got_packet) {
    LibWebPAnimContext *s = avctx->priv_data;
    int ret;

    if (!frame) {
        if (s->done) {  // Second flush: return empty package to denote finish.
            *got_packet = 0;
            return 0;
        } else {  // First flush: assemble bitstream and return it.
            WebPData assembled_data = { 0 };
            ret = WebPAnimEncoderAssemble(s->enc, &assembled_data);
            if (ret) {
                ret = ff_alloc_packet2(avctx, pkt, assembled_data.size, assembled_data.size);
                if (ret < 0)
                    return ret;
                memcpy(pkt->data, assembled_data.bytes, assembled_data.size);
                s->done = 1;
                pkt->flags |= AV_PKT_FLAG_KEY;
                pkt->pts = pkt->dts = s->prev_frame_pts + 1;
                *got_packet = 1;
                return 0;
            } else {
                av_log(s, AV_LOG_ERROR,
                       "WebPAnimEncoderAssemble() failed with error: %d\n",
                       VP8_ENC_ERROR_OUT_OF_MEMORY);
                return AVERROR(ENOMEM);
            }
        }
    } else {
        int timestamp_ms;
        WebPPicture *pic = NULL;
        AVFrame *alt_frame = NULL;
        ret = ff_libwebp_get_frame(avctx, &s->cc, frame, &alt_frame, &pic);
        if (ret < 0)
            goto end;

        timestamp_ms =
            avctx->time_base.num * frame->pts * 1000 / avctx->time_base.den;
        ret = WebPAnimEncoderAdd(s->enc, pic, timestamp_ms, &s->cc.config);
        if (!ret) {
                av_log(avctx, AV_LOG_ERROR,
                       "Encoding WebP frame failed with error: %d\n",
                   pic->error_code);
            ret = ff_libwebp_error_to_averror(pic->error_code);
            goto end;
        }

        pkt->pts = pkt->dts = frame->pts;
        s->prev_frame_pts = frame->pts;  // Save for next frame.
        ret = 0;
        *got_packet = 1;

end:
        WebPPictureFree(pic);
        av_freep(&pic);
        av_frame_free(&alt_frame);
        return ret;
    }
}