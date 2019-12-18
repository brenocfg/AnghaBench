#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxU16 ;
struct TYPE_11__ {int flags; scalar_t__ global_quality; scalar_t__ rc_max_rate; scalar_t__ bit_rate; } ;
struct TYPE_8__ {int /*<<< orphan*/  RateControlMethod; } ;
struct TYPE_9__ {TYPE_1__ mfx; } ;
struct TYPE_10__ {int look_ahead; int vcm; TYPE_2__ param; } ;
typedef  TYPE_3__ QSVEncContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CODEC_FLAG_QSCALE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  MFX_RATECONTROL_AVBR ; 
 int /*<<< orphan*/  MFX_RATECONTROL_CBR ; 
 int /*<<< orphan*/  MFX_RATECONTROL_CQP ; 
 int /*<<< orphan*/  MFX_RATECONTROL_ICQ ; 
 int /*<<< orphan*/  MFX_RATECONTROL_LA ; 
 int /*<<< orphan*/  MFX_RATECONTROL_LA_ICQ ; 
 int /*<<< orphan*/  MFX_RATECONTROL_QVBR ; 
 int /*<<< orphan*/  MFX_RATECONTROL_VBR ; 
 int /*<<< orphan*/  MFX_RATECONTROL_VCM ; 
 int /*<<< orphan*/  QSV_HAVE_ICQ ; 
 int /*<<< orphan*/  QSV_HAVE_LA ; 
 int /*<<< orphan*/  QSV_HAVE_VCM ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int select_rc_mode(AVCodecContext *avctx, QSVEncContext *q)
{
    const char *rc_desc;
    mfxU16      rc_mode;

    int want_la     = q->look_ahead;
    int want_qscale = !!(avctx->flags & AV_CODEC_FLAG_QSCALE);
    int want_vcm    = q->vcm;

    if (want_la && !QSV_HAVE_LA) {
        av_log(avctx, AV_LOG_ERROR,
               "Lookahead ratecontrol mode requested, but is not supported by this SDK version\n");
        return AVERROR(ENOSYS);
    }
    if (want_vcm && !QSV_HAVE_VCM) {
        av_log(avctx, AV_LOG_ERROR,
               "VCM ratecontrol mode requested, but is not supported by this SDK version\n");
        return AVERROR(ENOSYS);
    }

    if (want_la + want_qscale + want_vcm > 1) {
        av_log(avctx, AV_LOG_ERROR,
               "More than one of: { constant qscale, lookahead, VCM } requested, "
               "only one of them can be used at a time.\n");
        return AVERROR(EINVAL);
    }

    if (!want_qscale && avctx->global_quality > 0 && !QSV_HAVE_ICQ){
        av_log(avctx, AV_LOG_ERROR,
               "ICQ ratecontrol mode requested, but is not supported by this SDK version\n");
        return AVERROR(ENOSYS);
    }

    if (want_qscale) {
        rc_mode = MFX_RATECONTROL_CQP;
        rc_desc = "constant quantization parameter (CQP)";
    }
#if QSV_HAVE_VCM
    else if (want_vcm) {
        rc_mode = MFX_RATECONTROL_VCM;
        rc_desc = "video conferencing mode (VCM)";
    }
#endif
#if QSV_HAVE_LA
    else if (want_la) {
        rc_mode = MFX_RATECONTROL_LA;
        rc_desc = "VBR with lookahead (LA)";

#if QSV_HAVE_ICQ
        if (avctx->global_quality > 0) {
            rc_mode = MFX_RATECONTROL_LA_ICQ;
            rc_desc = "intelligent constant quality with lookahead (LA_ICQ)";
        }
#endif
    }
#endif
#if QSV_HAVE_ICQ
    else if (avctx->global_quality > 0 && !avctx->rc_max_rate) {
        rc_mode = MFX_RATECONTROL_ICQ;
        rc_desc = "intelligent constant quality (ICQ)";
    }
#endif
    else if (avctx->rc_max_rate == avctx->bit_rate) {
        rc_mode = MFX_RATECONTROL_CBR;
        rc_desc = "constant bitrate (CBR)";
    }
#if QSV_HAVE_AVBR
    else if (!avctx->rc_max_rate) {
        rc_mode = MFX_RATECONTROL_AVBR;
        rc_desc = "average variable bitrate (AVBR)";
    }
#endif
#if QSV_HAVE_QVBR
    else if (avctx->global_quality > 0) {
        rc_mode = MFX_RATECONTROL_QVBR;
        rc_desc = "constant quality with VBR algorithm (QVBR)";
    }
#endif
    else {
        rc_mode = MFX_RATECONTROL_VBR;
        rc_desc = "variable bitrate (VBR)";
    }

    q->param.mfx.RateControlMethod = rc_mode;
    av_log(avctx, AV_LOG_VERBOSE, "Using the %s ratecontrol method\n", rc_desc);

    return 0;
}