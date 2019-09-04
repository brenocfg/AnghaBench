#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* priv_data; } ;
struct TYPE_16__ {scalar_t__ size; int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {scalar_t__ ReadyListCount; int /*<<< orphan*/  member_0; } ;
struct TYPE_14__ {scalar_t__ draining; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ CopyRet ;
typedef  TYPE_1__ CHDContext ;
typedef  scalar_t__ BC_STATUS ;
typedef  TYPE_2__ BC_DTS_STATUS ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 scalar_t__ BC_STS_SUCCESS ; 
 scalar_t__ DtsGetDriverStatus (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ DtsTxFreeSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ RET_COPY_AGAIN ; 
 scalar_t__ RET_ERROR ; 
 scalar_t__ RET_OK ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int crystalhd_decode_packet (TYPE_4__*,TYPE_3__*) ; 
 int ff_decode_get_packet (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ receive_frame (TYPE_4__*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int crystalhd_receive_frame(AVCodecContext *avctx, AVFrame *frame)
{
    BC_STATUS bc_ret;
    BC_DTS_STATUS decoder_status = { 0, };
    CopyRet rec_ret;
    CHDContext *priv   = avctx->priv_data;
    HANDLE dev         = priv->dev;
    int got_frame = 0;
    int ret = 0;
    AVPacket pkt = {0};

    av_log(avctx, AV_LOG_VERBOSE, "CrystalHD: receive_frame\n");

    ret = ff_decode_get_packet(avctx, &pkt);
    if (ret < 0 && ret != AVERROR_EOF) {
        return ret;
    }

    while (pkt.size > DtsTxFreeSize(dev)) {
        /*
         * Block until there is space in the buffer for the next packet.
         * We assume that the hardware will make forward progress at this
         * point, although in pathological cases that may not happen.
         */
        av_log(avctx, AV_LOG_TRACE, "CrystalHD: Waiting for space in input buffer\n");
    }

    ret = crystalhd_decode_packet(avctx, &pkt);
    av_packet_unref(&pkt);
    // crystalhd_is_buffer_full() should avoid this.
    if (ret == AVERROR(EAGAIN)) {
        ret = AVERROR_EXTERNAL;
    }
    if (ret < 0 && ret != AVERROR_EOF) {
        return ret;
    }

    do {
        bc_ret = DtsGetDriverStatus(dev, &decoder_status);
        if (bc_ret != BC_STS_SUCCESS) {
            av_log(avctx, AV_LOG_ERROR, "CrystalHD: GetDriverStatus failed\n");
            return -1;
        }

        if (decoder_status.ReadyListCount == 0) {
            av_log(avctx, AV_LOG_VERBOSE, "CrystalHD: Insufficient frames ready. Returning\n");
            got_frame = 0;
            rec_ret = RET_OK;
            break;
        }

        rec_ret = receive_frame(avctx, frame, &got_frame);
    } while (rec_ret == RET_COPY_AGAIN);

    if (rec_ret == RET_ERROR) {
        return -1;
    } else if (got_frame == 0) {
        return priv->draining ? AVERROR_EOF : AVERROR(EAGAIN);
    } else {
        return 0;
    }
}