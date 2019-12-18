#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vpx_codec_enc_cfg {int rc_target_bitrate; scalar_t__ rc_end_usage; } ;
struct TYPE_5__ {int crf; } ;
typedef  TYPE_1__ VPxContext ;
struct TYPE_6__ {int bit_rate; TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ VPX_CQ ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void set_vp8_defaults(AVCodecContext *avctx,
                             struct vpx_codec_enc_cfg *enccfg)
{
    VPxContext *ctx = avctx->priv_data;
    av_assert0(!avctx->bit_rate);
    avctx->bit_rate = enccfg->rc_target_bitrate * 1000;
    if (enccfg->rc_end_usage == VPX_CQ) {
        av_log(avctx, AV_LOG_WARNING,
               "Bitrate not specified for constrained quality mode, using default of %dkbit/sec\n",
               enccfg->rc_target_bitrate);
    } else {
        enccfg->rc_end_usage = VPX_CQ;
        ctx->crf = 32;
        av_log(avctx, AV_LOG_WARNING,
               "Neither bitrate nor constrained quality specified, using default CRF of %d and bitrate of %dkbit/sec\n",
               ctx->crf, enccfg->rc_target_bitrate);
    }
}