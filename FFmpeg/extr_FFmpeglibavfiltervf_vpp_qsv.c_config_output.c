#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxExtVPPProcAmp ;
typedef  int /*<<< orphan*/  mfxExtVPPFrameRateConversion ;
typedef  int /*<<< orphan*/  mfxExtVPPDetail ;
typedef  int /*<<< orphan*/  mfxExtVPPDenoise ;
typedef  int /*<<< orphan*/  mfxExtVPPDeinterlacing ;
typedef  int /*<<< orphan*/  mfxExtBuffer ;
struct TYPE_12__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_18__ {int /*<<< orphan*/  Brightness; int /*<<< orphan*/  Contrast; int /*<<< orphan*/  Saturation; int /*<<< orphan*/  Hue; TYPE_1__ Header; scalar_t__ DetailFactor; scalar_t__ DenoiseFactor; int /*<<< orphan*/  Algorithm; int /*<<< orphan*/  Mode; } ;
struct TYPE_13__ {scalar_t__ out_width; scalar_t__ out_height; int deinterlace; int /*<<< orphan*/  qsv; scalar_t__ procamp; scalar_t__ detail; scalar_t__ denoise; scalar_t__ use_crop; scalar_t__ use_frc; TYPE_7__ procamp_conf; int /*<<< orphan*/  brightness; int /*<<< orphan*/  contrast; int /*<<< orphan*/  saturation; int /*<<< orphan*/  hue; TYPE_7__ detail_conf; TYPE_7__ denoise_conf; TYPE_7__ frc_conf; TYPE_7__ deinterlace_conf; int /*<<< orphan*/  crop_h; int /*<<< orphan*/  crop_w; int /*<<< orphan*/  crop_y; int /*<<< orphan*/  crop_x; int /*<<< orphan*/  framerate; } ;
typedef  TYPE_2__ VPPContext ;
struct TYPE_17__ {TYPE_5__** inputs; TYPE_2__* priv; } ;
struct TYPE_16__ {scalar_t__ w; scalar_t__ h; scalar_t__ hw_frames_ctx; int /*<<< orphan*/  time_base; int /*<<< orphan*/  frame_rate; TYPE_6__* src; } ;
struct TYPE_15__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; scalar_t__ in_idx; int /*<<< orphan*/  member_0; } ;
struct TYPE_14__ {int num_crop; scalar_t__ num_ext_buf; int /*<<< orphan*/ ** ext_buf; TYPE_4__* crop; int /*<<< orphan*/  out_sw_format; int /*<<< orphan*/ * filter_frame; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_3__ QSVVPPParam ;
typedef  TYPE_4__ QSVVPPCrop ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  AV_PIX_FMT_NV12 ; 
 int ENH_FILTERS_COUNT ; 
 int /*<<< orphan*/  MFX_DEINTERLACING_ADVANCED ; 
 int /*<<< orphan*/  MFX_DEINTERLACING_BOB ; 
 int /*<<< orphan*/  MFX_EXTBUFF_VPP_DEINTERLACING ; 
 int /*<<< orphan*/  MFX_EXTBUFF_VPP_DENOISE ; 
 int /*<<< orphan*/  MFX_EXTBUFF_VPP_DETAIL ; 
 int /*<<< orphan*/  MFX_EXTBUFF_VPP_FRAME_RATE_CONVERSION ; 
 int /*<<< orphan*/  MFX_EXTBUFF_VPP_PROCAMP ; 
 int /*<<< orphan*/  MFX_FRCALGM_DISTRIBUTED_TIMESTAMP ; 
 scalar_t__ av_buffer_ref (scalar_t__) ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int ff_qsvvpp_create (TYPE_6__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    VPPContext      *vpp = ctx->priv;
    QSVVPPParam     param = { NULL };
    QSVVPPCrop      crop  = { 0 };
    mfxExtBuffer    *ext_buf[ENH_FILTERS_COUNT];
    AVFilterLink    *inlink = ctx->inputs[0];

    outlink->w          = vpp->out_width;
    outlink->h          = vpp->out_height;
    outlink->frame_rate = vpp->framerate;
    outlink->time_base  = av_inv_q(vpp->framerate);

    param.filter_frame  = NULL;
    param.out_sw_format = AV_PIX_FMT_NV12;
    param.num_ext_buf   = 0;
    param.ext_buf       = ext_buf;

    if (vpp->use_crop) {
        crop.in_idx = 0;
        crop.x = vpp->crop_x;
        crop.y = vpp->crop_y;
        crop.w = vpp->crop_w;
        crop.h = vpp->crop_h;

        param.num_crop = 1;
        param.crop     = &crop;
    }

    if (vpp->deinterlace) {
        memset(&vpp->deinterlace_conf, 0, sizeof(mfxExtVPPDeinterlacing));
        vpp->deinterlace_conf.Header.BufferId = MFX_EXTBUFF_VPP_DEINTERLACING;
        vpp->deinterlace_conf.Header.BufferSz = sizeof(mfxExtVPPDeinterlacing);
        vpp->deinterlace_conf.Mode = vpp->deinterlace == 1 ?
                                     MFX_DEINTERLACING_BOB : MFX_DEINTERLACING_ADVANCED;

        param.ext_buf[param.num_ext_buf++] = (mfxExtBuffer*)&vpp->deinterlace_conf;
    }

    if (vpp->use_frc) {
        memset(&vpp->frc_conf, 0, sizeof(mfxExtVPPFrameRateConversion));
        vpp->frc_conf.Header.BufferId = MFX_EXTBUFF_VPP_FRAME_RATE_CONVERSION;
        vpp->frc_conf.Header.BufferSz = sizeof(mfxExtVPPFrameRateConversion);
        vpp->frc_conf.Algorithm = MFX_FRCALGM_DISTRIBUTED_TIMESTAMP;

        param.ext_buf[param.num_ext_buf++] = (mfxExtBuffer*)&vpp->frc_conf;
    }

    if (vpp->denoise) {
        memset(&vpp->denoise_conf, 0, sizeof(mfxExtVPPDenoise));
        vpp->denoise_conf.Header.BufferId = MFX_EXTBUFF_VPP_DENOISE;
        vpp->denoise_conf.Header.BufferSz = sizeof(mfxExtVPPDenoise);
        vpp->denoise_conf.DenoiseFactor   = vpp->denoise;

        param.ext_buf[param.num_ext_buf++] = (mfxExtBuffer*)&vpp->denoise_conf;
    }

    if (vpp->detail) {
        memset(&vpp->detail_conf, 0, sizeof(mfxExtVPPDetail));
        vpp->detail_conf.Header.BufferId  = MFX_EXTBUFF_VPP_DETAIL;
        vpp->detail_conf.Header.BufferSz  = sizeof(mfxExtVPPDetail);
        vpp->detail_conf.DetailFactor = vpp->detail;

        param.ext_buf[param.num_ext_buf++] = (mfxExtBuffer*)&vpp->detail_conf;
    }

    if (vpp->procamp) {
        memset(&vpp->procamp_conf, 0, sizeof(mfxExtVPPProcAmp));
        vpp->procamp_conf.Header.BufferId  = MFX_EXTBUFF_VPP_PROCAMP;
        vpp->procamp_conf.Header.BufferSz  = sizeof(mfxExtVPPProcAmp);
        vpp->procamp_conf.Hue              = vpp->hue;
        vpp->procamp_conf.Saturation       = vpp->saturation;
        vpp->procamp_conf.Contrast         = vpp->contrast;
        vpp->procamp_conf.Brightness       = vpp->brightness;

        param.ext_buf[param.num_ext_buf++] = (mfxExtBuffer*)&vpp->procamp_conf;
    }

    if (vpp->use_frc || vpp->use_crop || vpp->deinterlace || vpp->denoise ||
        vpp->detail || vpp->procamp || inlink->w != outlink->w || inlink->h != outlink->h)
        return ff_qsvvpp_create(ctx, &vpp->qsv, &param);
    else {
        av_log(ctx, AV_LOG_VERBOSE, "qsv vpp pass through mode.\n");
        if (inlink->hw_frames_ctx)
            outlink->hw_frames_ctx = av_buffer_ref(inlink->hw_frames_ctx);
    }

    return 0;
}