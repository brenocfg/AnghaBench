#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ cutoff; int /*<<< orphan*/  bit_rate; scalar_t__ global_quality; } ;
struct TYPE_6__ {int vbr; int /*<<< orphan*/  apply_phase_inv; int /*<<< orphan*/  max_bandwidth; int /*<<< orphan*/  packet_loss; int /*<<< orphan*/  complexity; } ;
typedef  int /*<<< orphan*/  OpusMSEncoder ;
typedef  TYPE_1__ LibopusEncOpts ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int OPUS_OK ; 
 int /*<<< orphan*/  OPUS_SET_BITRATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPUS_SET_COMPLEXITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPUS_SET_MAX_BANDWIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPUS_SET_PACKET_LOSS_PERC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPUS_SET_PHASE_INVERSION_DISABLED (int) ; 
 int /*<<< orphan*/  OPUS_SET_VBR (int) ; 
 int /*<<< orphan*/  OPUS_SET_VBR_CONSTRAINT (int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int opus_multistream_encoder_ctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opus_strerror (int) ; 

__attribute__((used)) static int libopus_configure_encoder(AVCodecContext *avctx, OpusMSEncoder *enc,
                                     LibopusEncOpts *opts)
{
    int ret;

    if (avctx->global_quality) {
        av_log(avctx, AV_LOG_ERROR,
               "Quality-based encoding not supported, "
               "please specify a bitrate and VBR setting.\n");
        return AVERROR(EINVAL);
    }

    ret = opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(avctx->bit_rate));
    if (ret != OPUS_OK) {
        av_log(avctx, AV_LOG_ERROR,
               "Failed to set bitrate: %s\n", opus_strerror(ret));
        return ret;
    }

    ret = opus_multistream_encoder_ctl(enc,
                                       OPUS_SET_COMPLEXITY(opts->complexity));
    if (ret != OPUS_OK)
        av_log(avctx, AV_LOG_WARNING,
               "Unable to set complexity: %s\n", opus_strerror(ret));

    ret = opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(!!opts->vbr));
    if (ret != OPUS_OK)
        av_log(avctx, AV_LOG_WARNING,
               "Unable to set VBR: %s\n", opus_strerror(ret));

    ret = opus_multistream_encoder_ctl(enc,
                                       OPUS_SET_VBR_CONSTRAINT(opts->vbr == 2));
    if (ret != OPUS_OK)
        av_log(avctx, AV_LOG_WARNING,
               "Unable to set constrained VBR: %s\n", opus_strerror(ret));

    ret = opus_multistream_encoder_ctl(enc,
                                       OPUS_SET_PACKET_LOSS_PERC(opts->packet_loss));
    if (ret != OPUS_OK)
        av_log(avctx, AV_LOG_WARNING,
               "Unable to set expected packet loss percentage: %s\n",
               opus_strerror(ret));

    if (avctx->cutoff) {
        ret = opus_multistream_encoder_ctl(enc,
                                           OPUS_SET_MAX_BANDWIDTH(opts->max_bandwidth));
        if (ret != OPUS_OK)
            av_log(avctx, AV_LOG_WARNING,
                   "Unable to set maximum bandwidth: %s\n", opus_strerror(ret));
    }

#ifdef OPUS_SET_PHASE_INVERSION_DISABLED_REQUEST
    ret = opus_multistream_encoder_ctl(enc,
                                       OPUS_SET_PHASE_INVERSION_DISABLED(!opts->apply_phase_inv));
    if (ret != OPUS_OK)
        av_log(avctx, AV_LOG_WARNING,
               "Unable to set phase inversion: %s\n",
               opus_strerror(ret));
#endif
    return OPUS_OK;
}