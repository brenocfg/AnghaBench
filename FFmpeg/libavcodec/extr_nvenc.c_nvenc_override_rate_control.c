#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  qmin; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  rateControlMode; } ;
struct TYPE_9__ {TYPE_3__ rcParams; } ;
struct TYPE_10__ {int rc; TYPE_1__ encode_config; } ;
typedef  TYPE_2__ NvencContext ;
typedef  TYPE_3__ NV_ENC_RC_PARAMS ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
#define  NV_ENC_PARAMS_RC_CBR 134 
#define  NV_ENC_PARAMS_RC_CBR_HQ 133 
#define  NV_ENC_PARAMS_RC_CBR_LOWDELAY_HQ 132 
#define  NV_ENC_PARAMS_RC_CONSTQP 131 
#define  NV_ENC_PARAMS_RC_VBR 130 
#define  NV_ENC_PARAMS_RC_VBR_HQ 129 
#define  NV_ENC_PARAMS_RC_VBR_MINQP 128 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_constqp (TYPE_4__*) ; 
 int /*<<< orphan*/  set_vbr (TYPE_4__*) ; 

__attribute__((used)) static void nvenc_override_rate_control(AVCodecContext *avctx)
{
    NvencContext *ctx    = avctx->priv_data;
    NV_ENC_RC_PARAMS *rc = &ctx->encode_config.rcParams;

    switch (ctx->rc) {
    case NV_ENC_PARAMS_RC_CONSTQP:
        set_constqp(avctx);
        return;
    case NV_ENC_PARAMS_RC_VBR_MINQP:
        if (avctx->qmin < 0) {
            av_log(avctx, AV_LOG_WARNING,
                   "The variable bitrate rate-control requires "
                   "the 'qmin' option set.\n");
            set_vbr(avctx);
            return;
        }
        /* fall through */
    case NV_ENC_PARAMS_RC_VBR_HQ:
    case NV_ENC_PARAMS_RC_VBR:
        set_vbr(avctx);
        break;
    case NV_ENC_PARAMS_RC_CBR:
    case NV_ENC_PARAMS_RC_CBR_HQ:
    case NV_ENC_PARAMS_RC_CBR_LOWDELAY_HQ:
        break;
    }

    rc->rateControlMode = ctx->rc;
}