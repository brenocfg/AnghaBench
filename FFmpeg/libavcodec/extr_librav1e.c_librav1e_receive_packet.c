#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  bsf; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ librav1eContext ;
struct TYPE_21__ {int flags; int ticks_per_frame; TYPE_1__* internal; TYPE_2__* priv_data; } ;
struct TYPE_20__ {int pts; int dts; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {scalar_t__ frame_type; int input_frameno; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_17__ {int /*<<< orphan*/  draining; } ;
typedef  TYPE_3__ RaPacket ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_EXTERNAL ; 
 int AVERROR_UNKNOWN ; 
 int AV_CODEC_FLAG_GLOBAL_HEADER ; 
 int AV_CODEC_FLAG_PASS1 ; 
 int AV_CODEC_FLAG_PASS2 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EAGAIN ; 
#define  RA_ENCODER_STATUS_ENCODED 132 
#define  RA_ENCODER_STATUS_FAILURE 131 
#define  RA_ENCODER_STATUS_LIMIT_REACHED 130 
#define  RA_ENCODER_STATUS_NEED_MORE_DATA 129 
#define  RA_ENCODER_STATUS_SUCCESS 128 
 scalar_t__ RA_FRAME_TYPE_KEY ; 
 int av_bsf_receive_packet (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int av_bsf_send_packet (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_new_packet (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_4__*) ; 
 int get_stats (TYPE_5__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rav1e_packet_unref (TYPE_3__*) ; 
 int rav1e_receive_packet (int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  rav1e_status_to_str (int) ; 
 int set_stats (TYPE_5__*) ; 

__attribute__((used)) static int librav1e_receive_packet(AVCodecContext *avctx, AVPacket *pkt)
{
    librav1eContext *ctx = avctx->priv_data;
    RaPacket *rpkt = NULL;
    int ret;

retry:

    if (avctx->flags & AV_CODEC_FLAG_PASS1) {
        int sret = get_stats(avctx, 0);
        if (sret < 0)
            return sret;
    } else if (avctx->flags & AV_CODEC_FLAG_PASS2) {
        int sret = set_stats(avctx);
        if (sret < 0)
            return sret;
    }

    ret = rav1e_receive_packet(ctx->ctx, &rpkt);
    switch (ret) {
    case RA_ENCODER_STATUS_SUCCESS:
        break;
    case RA_ENCODER_STATUS_LIMIT_REACHED:
        if (avctx->flags & AV_CODEC_FLAG_PASS1) {
            int sret = get_stats(avctx, 1);
            if (sret < 0)
                return sret;
        }
        return AVERROR_EOF;
    case RA_ENCODER_STATUS_ENCODED:
        if (avctx->internal->draining)
            goto retry;
        return AVERROR(EAGAIN);
    case RA_ENCODER_STATUS_NEED_MORE_DATA:
        if (avctx->internal->draining) {
            av_log(avctx, AV_LOG_ERROR, "Unexpected error when receiving packet after EOF.\n");
            return AVERROR_EXTERNAL;
        }
        return AVERROR(EAGAIN);
    case RA_ENCODER_STATUS_FAILURE:
        av_log(avctx, AV_LOG_ERROR, "Could not encode frame: %s\n", rav1e_status_to_str(ret));
        return AVERROR_EXTERNAL;
    default:
        av_log(avctx, AV_LOG_ERROR, "Unknown return code %d from rav1e_receive_packet: %s\n", ret, rav1e_status_to_str(ret));
        return AVERROR_UNKNOWN;
    }

    ret = av_new_packet(pkt, rpkt->len);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Could not allocate packet.\n");
        rav1e_packet_unref(rpkt);
        return ret;
    }

    memcpy(pkt->data, rpkt->data, rpkt->len);

    if (rpkt->frame_type == RA_FRAME_TYPE_KEY)
        pkt->flags |= AV_PKT_FLAG_KEY;

    pkt->pts = pkt->dts = rpkt->input_frameno * avctx->ticks_per_frame;
    rav1e_packet_unref(rpkt);

    if (avctx->flags & AV_CODEC_FLAG_GLOBAL_HEADER) {
        int ret = av_bsf_send_packet(ctx->bsf, pkt);
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR, "extradata extraction send failed.\n");
            av_packet_unref(pkt);
            return ret;
        }

        ret = av_bsf_receive_packet(ctx->bsf, pkt);
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR, "extradata extraction receive failed.\n");
            av_packet_unref(pkt);
            return ret;
        }
    }

    return 0;
}