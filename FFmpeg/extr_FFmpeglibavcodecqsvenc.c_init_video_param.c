#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_17__ ;
typedef  struct TYPE_32__   TYPE_16__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxExtBuffer ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_40__ {int BitDepthLuma; int BitDepthChroma; int Shift; scalar_t__ FrameRateExtN; scalar_t__ FrameRateExtD; void* Height; void* Width; int /*<<< orphan*/  PicStruct; int /*<<< orphan*/  ChromaFormat; int /*<<< orphan*/  AspectRatioH; int /*<<< orphan*/  AspectRatioW; int /*<<< orphan*/  CropH; int /*<<< orphan*/  CropW; scalar_t__ CropY; scalar_t__ CropX; int /*<<< orphan*/  FourCC; } ;
struct TYPE_42__ {int CodecId; scalar_t__ CodecLevel; scalar_t__ TargetUsage; int GopPicSize; int GopRefDist; int NumRefFrame; int BufferSizeInKB; int RateControlMethod; int InitialDelayInKB; int TargetKbps; int MaxKbps; int BRCParamMultiplier; void* QPB; void* QPP; void* QPI; TYPE_7__ FrameInfo; scalar_t__ EncodedOrder; int /*<<< orphan*/  NumSlice; int /*<<< orphan*/  IdrInterval; int /*<<< orphan*/  GopOptFlag; int /*<<< orphan*/  CodecProfile; void* LowPower; } ;
struct TYPE_41__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_39__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_37__ {void* Height; void* Width; } ;
struct TYPE_38__ {TYPE_4__ Info; } ;
struct TYPE_36__ {scalar_t__ data; } ;
struct TYPE_35__ {int depth; } ;
struct TYPE_34__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_33__ {scalar_t__ pix_fmt; int sw_pix_fmt; scalar_t__ codec_id; scalar_t__ level; scalar_t__ compression_level; int gop_size; int max_b_frames; int flags; int refs; int rc_buffer_size; int rc_initial_buffer_occupancy; int bit_rate; int rc_max_rate; float global_quality; scalar_t__ strict_std_compliance; int /*<<< orphan*/  b_quant_offset; int /*<<< orphan*/  b_quant_factor; int /*<<< orphan*/  i_quant_offset; int /*<<< orphan*/  i_quant_factor; TYPE_8__ time_base; TYPE_6__ framerate; TYPE_3__* hw_frames_ctx; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ sample_aspect_ratio; int /*<<< orphan*/  slices; } ;
struct TYPE_32__ {TYPE_14__* hwctx; } ;
struct TYPE_31__ {TYPE_2__* comp; } ;
struct TYPE_30__ {TYPE_5__* surfaces; } ;
struct TYPE_27__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_28__ {void* AUDelimiter; int /*<<< orphan*/  MaxDecFrameBuffering; void* RecoveryPointSEI; void* SingleSeiNalUnit; void* NalHrdConformance; void* CAVLC; void* RateDistortionOpt; void* PicTimingSEI; TYPE_11__ Header; } ;
struct TYPE_26__ {TYPE_9__ mfx; } ;
struct TYPE_29__ {scalar_t__ preset; int width_align; int height_align; scalar_t__ rdo; scalar_t__ single_sei_nal_unit; scalar_t__ recovery_point_sei; TYPE_12__ extco; int /*<<< orphan*/  nb_extparam_internal; int /*<<< orphan*/ ** extparam_internal; scalar_t__ aud; int /*<<< orphan*/  max_dec_frame_buffering; scalar_t__ cavlc; scalar_t__ pic_timing_sei; int /*<<< orphan*/  ver; TYPE_10__ param; int /*<<< orphan*/  idr_interval; int /*<<< orphan*/  profile; scalar_t__ low_power; } ;
typedef  TYPE_13__ QSVEncContext ;
typedef  TYPE_14__ AVQSVFramesContext ;
typedef  TYPE_15__ AVPixFmtDescriptor ;
typedef  TYPE_16__ AVHWFramesContext ;
typedef  TYPE_17__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int AV_CODEC_FLAG_CLOSED_GOP ; 
 int AV_CODEC_FLAG_INTERLACED_DCT ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_HEVC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PIX_FMT_QSV ; 
 int /*<<< orphan*/  ENOSYS ; 
 void* FFALIGN (int /*<<< orphan*/ ,int) ; 
 int FFMAX (int,int) ; 
 int FFMAX3 (int,int,int) ; 
 scalar_t__ FF_COMPLIANCE_NORMAL ; 
 scalar_t__ FF_COMPRESSION_DEFAULT ; 
 float FF_QP2LAMBDA ; 
 int /*<<< orphan*/  MFX_CHROMAFORMAT_YUV420 ; 
 void* MFX_CODINGOPTION_OFF ; 
 void* MFX_CODINGOPTION_ON ; 
 void* MFX_CODINGOPTION_UNKNOWN ; 
 int /*<<< orphan*/  MFX_EXTBUFF_CODING_OPTION ; 
 int /*<<< orphan*/  MFX_GOP_CLOSED ; 
 int /*<<< orphan*/  MFX_PICSTRUCT_FIELD_TFF ; 
 int /*<<< orphan*/  MFX_PICSTRUCT_PROGRESSIVE ; 
#define  MFX_RATECONTROL_CBR 130 
#define  MFX_RATECONTROL_CQP 129 
#define  MFX_RATECONTROL_VBR 128 
 scalar_t__ MFX_TARGETUSAGE_BEST_SPEED ; 
 scalar_t__ QSV_RUNTIME_VERSION_ATLEAST (int /*<<< orphan*/ ,int,int) ; 
 void* av_clip (float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_17__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_15__* av_pix_fmt_desc_get (int) ; 
 int /*<<< orphan*/  check_enc_param (TYPE_17__*,TYPE_13__*) ; 
 float fabs (int /*<<< orphan*/ ) ; 
 int ff_qsv_codec_id_to_mfx (scalar_t__) ; 
 int /*<<< orphan*/  ff_qsv_map_pixfmt (int,int /*<<< orphan*/ *) ; 
 int select_rc_mode (TYPE_17__*,TYPE_13__*) ; 

__attribute__((used)) static int init_video_param(AVCodecContext *avctx, QSVEncContext *q)
{
    enum AVPixelFormat sw_format = avctx->pix_fmt == AV_PIX_FMT_QSV ?
                                   avctx->sw_pix_fmt : avctx->pix_fmt;
    const AVPixFmtDescriptor *desc;
    float quant;
    int target_bitrate_kbps, max_bitrate_kbps, brc_param_multiplier;
    int buffer_size_in_kilobytes, initial_delay_in_kilobytes;
    int ret;

    ret = ff_qsv_codec_id_to_mfx(avctx->codec_id);
    if (ret < 0)
        return AVERROR_BUG;
    q->param.mfx.CodecId = ret;

    if (avctx->level > 0)
        q->param.mfx.CodecLevel = avctx->level;

    if (avctx->compression_level == FF_COMPRESSION_DEFAULT) {
        avctx->compression_level = q->preset;
    } else if (avctx->compression_level >= 0) {
        if (avctx->compression_level > MFX_TARGETUSAGE_BEST_SPEED) {
            av_log(avctx, AV_LOG_WARNING, "Invalid compression level: "
                    "valid range is 0-%d, using %d instead\n",
                    MFX_TARGETUSAGE_BEST_SPEED, MFX_TARGETUSAGE_BEST_SPEED);
            avctx->compression_level = MFX_TARGETUSAGE_BEST_SPEED;
        }
    }

    if (q->low_power) {
#if QSV_HAVE_VDENC
        q->param.mfx.LowPower = MFX_CODINGOPTION_ON;
#else
        av_log(avctx, AV_LOG_WARNING, "The low_power option is "
                            "not supported with this MSDK version.\n");
        q->low_power = 0;
        q->param.mfx.LowPower = MFX_CODINGOPTION_OFF;
#endif
    } else
        q->param.mfx.LowPower = MFX_CODINGOPTION_OFF;

    q->param.mfx.CodecProfile       = q->profile;
    q->param.mfx.TargetUsage        = avctx->compression_level;
    q->param.mfx.GopPicSize         = FFMAX(0, avctx->gop_size);
    q->param.mfx.GopRefDist         = FFMAX(-1, avctx->max_b_frames) + 1;
    q->param.mfx.GopOptFlag         = avctx->flags & AV_CODEC_FLAG_CLOSED_GOP ?
                                      MFX_GOP_CLOSED : 0;
    q->param.mfx.IdrInterval        = q->idr_interval;
    q->param.mfx.NumSlice           = avctx->slices;
    q->param.mfx.NumRefFrame        = FFMAX(0, avctx->refs);
    q->param.mfx.EncodedOrder       = 0;
    q->param.mfx.BufferSizeInKB     = 0;

    desc = av_pix_fmt_desc_get(sw_format);
    if (!desc)
        return AVERROR_BUG;

    ff_qsv_map_pixfmt(sw_format, &q->param.mfx.FrameInfo.FourCC);

    q->param.mfx.FrameInfo.CropX          = 0;
    q->param.mfx.FrameInfo.CropY          = 0;
    q->param.mfx.FrameInfo.CropW          = avctx->width;
    q->param.mfx.FrameInfo.CropH          = avctx->height;
    q->param.mfx.FrameInfo.AspectRatioW   = avctx->sample_aspect_ratio.num;
    q->param.mfx.FrameInfo.AspectRatioH   = avctx->sample_aspect_ratio.den;
    q->param.mfx.FrameInfo.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    q->param.mfx.FrameInfo.BitDepthLuma   = desc->comp[0].depth;
    q->param.mfx.FrameInfo.BitDepthChroma = desc->comp[0].depth;
    q->param.mfx.FrameInfo.Shift          = desc->comp[0].depth > 8;

    // If the minor version is greater than or equal to 19,
    // then can use the same alignment settings as H.264 for HEVC
    q->width_align = (avctx->codec_id != AV_CODEC_ID_HEVC ||
                      QSV_RUNTIME_VERSION_ATLEAST(q->ver, 1, 19)) ? 16 : 32;
    q->param.mfx.FrameInfo.Width = FFALIGN(avctx->width, q->width_align);

    if (avctx->flags & AV_CODEC_FLAG_INTERLACED_DCT) {
        // it is important that PicStruct be setup correctly from the
        // start--otherwise, encoding doesn't work and results in a bunch
        // of incompatible video parameter errors
        q->param.mfx.FrameInfo.PicStruct = MFX_PICSTRUCT_FIELD_TFF;
        // height alignment always must be 32 for interlaced video
        q->height_align = 32;
    } else {
        q->param.mfx.FrameInfo.PicStruct = MFX_PICSTRUCT_PROGRESSIVE;
        // for progressive video, the height should be aligned to 16 for
        // H.264.  For HEVC, depending on the version of MFX, it should be
        // either 32 or 16.  The lower number is better if possible.
        q->height_align = avctx->codec_id == AV_CODEC_ID_HEVC ? 32 : 16;
    }
    q->param.mfx.FrameInfo.Height = FFALIGN(avctx->height, q->height_align);

    if (avctx->hw_frames_ctx) {
        AVHWFramesContext *frames_ctx = (AVHWFramesContext*)avctx->hw_frames_ctx->data;
        AVQSVFramesContext *frames_hwctx = frames_ctx->hwctx;
        q->param.mfx.FrameInfo.Width  = frames_hwctx->surfaces[0].Info.Width;
        q->param.mfx.FrameInfo.Height = frames_hwctx->surfaces[0].Info.Height;
    }

    if (avctx->framerate.den > 0 && avctx->framerate.num > 0) {
        q->param.mfx.FrameInfo.FrameRateExtN = avctx->framerate.num;
        q->param.mfx.FrameInfo.FrameRateExtD = avctx->framerate.den;
    } else {
        q->param.mfx.FrameInfo.FrameRateExtN  = avctx->time_base.den;
        q->param.mfx.FrameInfo.FrameRateExtD  = avctx->time_base.num;
    }

    ret = select_rc_mode(avctx, q);
    if (ret < 0)
        return ret;

    //libmfx BRC parameters are 16 bits thus maybe overflow, then BRCParamMultiplier is needed
    buffer_size_in_kilobytes   = avctx->rc_buffer_size / 8000;
    initial_delay_in_kilobytes = avctx->rc_initial_buffer_occupancy / 1000;
    target_bitrate_kbps        = avctx->bit_rate / 1000;
    max_bitrate_kbps           = avctx->rc_max_rate / 1000;
    brc_param_multiplier       = (FFMAX(FFMAX3(target_bitrate_kbps, max_bitrate_kbps, buffer_size_in_kilobytes),
                                  initial_delay_in_kilobytes) + 0x10000) / 0x10000;

    switch (q->param.mfx.RateControlMethod) {
    case MFX_RATECONTROL_CBR:
    case MFX_RATECONTROL_VBR:
#if QSV_HAVE_VCM
    case MFX_RATECONTROL_VCM:
#endif
#if QSV_HAVE_QVBR
    case MFX_RATECONTROL_QVBR:
#endif
        q->param.mfx.BufferSizeInKB   = buffer_size_in_kilobytes / brc_param_multiplier;
        q->param.mfx.InitialDelayInKB = initial_delay_in_kilobytes / brc_param_multiplier;
        q->param.mfx.TargetKbps       = target_bitrate_kbps / brc_param_multiplier;
        q->param.mfx.MaxKbps          = max_bitrate_kbps / brc_param_multiplier;
        q->param.mfx.BRCParamMultiplier = brc_param_multiplier;
#if QSV_HAVE_QVBR
        if (q->param.mfx.RateControlMethod == MFX_RATECONTROL_QVBR)
            q->extco3.QVBRQuality = av_clip(avctx->global_quality, 0, 51);
#endif
        break;
    case MFX_RATECONTROL_CQP:
        quant = avctx->global_quality / FF_QP2LAMBDA;

        q->param.mfx.QPI = av_clip(quant * fabs(avctx->i_quant_factor) + avctx->i_quant_offset, 0, 51);
        q->param.mfx.QPP = av_clip(quant, 0, 51);
        q->param.mfx.QPB = av_clip(quant * fabs(avctx->b_quant_factor) + avctx->b_quant_offset, 0, 51);

        break;
#if QSV_HAVE_AVBR
    case MFX_RATECONTROL_AVBR:
        q->param.mfx.TargetKbps  = target_bitrate_kbps / brc_param_multiplier;
        q->param.mfx.Convergence = q->avbr_convergence;
        q->param.mfx.Accuracy    = q->avbr_accuracy;
        q->param.mfx.BRCParamMultiplier = brc_param_multiplier;
        break;
#endif
#if QSV_HAVE_LA
    case MFX_RATECONTROL_LA:
        q->param.mfx.TargetKbps  = target_bitrate_kbps / brc_param_multiplier;
        q->extco2.LookAheadDepth = q->look_ahead_depth;
        q->param.mfx.BRCParamMultiplier = brc_param_multiplier;
        break;
#if QSV_HAVE_ICQ
    case MFX_RATECONTROL_LA_ICQ:
        q->extco2.LookAheadDepth = q->look_ahead_depth;
    case MFX_RATECONTROL_ICQ:
        q->param.mfx.ICQQuality  = avctx->global_quality;
        break;
#endif
#endif
    }

    // The HEVC encoder plugin currently fails with some old libmfx version if coding options
    // are provided. Can't find the extract libmfx version which fixed it, just enable it from
    // V1.28 in order to keep compatibility security.
    if ((avctx->codec_id != AV_CODEC_ID_HEVC) || QSV_RUNTIME_VERSION_ATLEAST(q->ver, 1, 28)) {
        q->extco.Header.BufferId      = MFX_EXTBUFF_CODING_OPTION;
        q->extco.Header.BufferSz      = sizeof(q->extco);

        q->extco.PicTimingSEI         = q->pic_timing_sei ?
                                        MFX_CODINGOPTION_ON : MFX_CODINGOPTION_UNKNOWN;

        if (q->rdo >= 0)
            q->extco.RateDistortionOpt = q->rdo > 0 ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;

        if (avctx->codec_id == AV_CODEC_ID_H264) {
#if FF_API_CODER_TYPE
FF_DISABLE_DEPRECATION_WARNINGS
            if (avctx->coder_type >= 0)
                q->cavlc = avctx->coder_type == FF_CODER_TYPE_VLC;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
            q->extco.CAVLC = q->cavlc ? MFX_CODINGOPTION_ON
                                      : MFX_CODINGOPTION_UNKNOWN;

            if (avctx->strict_std_compliance != FF_COMPLIANCE_NORMAL)
                q->extco.NalHrdConformance = avctx->strict_std_compliance > FF_COMPLIANCE_NORMAL ?
                                             MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;

            if (q->single_sei_nal_unit >= 0)
                q->extco.SingleSeiNalUnit = q->single_sei_nal_unit ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;
            if (q->recovery_point_sei >= 0)
                q->extco.RecoveryPointSEI = q->recovery_point_sei ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;
            q->extco.MaxDecFrameBuffering = q->max_dec_frame_buffering;
            q->extco.AUDelimiter          = q->aud ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;
        }

        q->extparam_internal[q->nb_extparam_internal++] = (mfxExtBuffer *)&q->extco;

        if (avctx->codec_id == AV_CODEC_ID_H264) {
#if QSV_HAVE_CO2
            q->extco2.Header.BufferId     = MFX_EXTBUFF_CODING_OPTION2;
            q->extco2.Header.BufferSz     = sizeof(q->extco2);

            if (q->int_ref_type >= 0)
                q->extco2.IntRefType = q->int_ref_type;
            if (q->int_ref_cycle_size >= 0)
                q->extco2.IntRefCycleSize = q->int_ref_cycle_size;
            if (q->int_ref_qp_delta != INT16_MIN)
                q->extco2.IntRefQPDelta = q->int_ref_qp_delta;

            if (q->bitrate_limit >= 0)
                q->extco2.BitrateLimit = q->bitrate_limit ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;
            if (q->mbbrc >= 0)
                q->extco2.MBBRC = q->mbbrc ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;
            if (q->extbrc >= 0)
                q->extco2.ExtBRC = q->extbrc ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;

            if (q->max_frame_size >= 0)
                q->extco2.MaxFrameSize = q->max_frame_size;
#if QSV_HAVE_MAX_SLICE_SIZE
            if (q->max_slice_size >= 0)
                q->extco2.MaxSliceSize = q->max_slice_size;
#endif

#if QSV_HAVE_TRELLIS
            if (avctx->trellis >= 0)
                q->extco2.Trellis = (avctx->trellis == 0) ? MFX_TRELLIS_OFF : (MFX_TRELLIS_I | MFX_TRELLIS_P | MFX_TRELLIS_B);
            else
                q->extco2.Trellis = MFX_TRELLIS_UNKNOWN;
#endif

#if QSV_VERSION_ATLEAST(1, 8)
            q->extco2.LookAheadDS = q->look_ahead_downsampling;
            q->extco2.RepeatPPS   = q->repeat_pps ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;

#if FF_API_PRIVATE_OPT
FF_DISABLE_DEPRECATION_WARNINGS
            if (avctx->b_frame_strategy >= 0)
                q->b_strategy = avctx->b_frame_strategy;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
            if (q->b_strategy >= 0)
                q->extco2.BRefType = q->b_strategy ? MFX_B_REF_PYRAMID : MFX_B_REF_OFF;
            if (q->adaptive_i >= 0)
                q->extco2.AdaptiveI = q->adaptive_i ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;
            if (q->adaptive_b >= 0)
                q->extco2.AdaptiveB = q->adaptive_b ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;
#endif

#if QSV_VERSION_ATLEAST(1, 9)
            if (avctx->qmin >= 0 && avctx->qmax >= 0 && avctx->qmin > avctx->qmax) {
                av_log(avctx, AV_LOG_ERROR, "qmin and or qmax are set but invalid, please make sure min <= max\n");
                return AVERROR(EINVAL);
            }
            if (avctx->qmin >= 0) {
                q->extco2.MinQPI = avctx->qmin > 51 ? 51 : avctx->qmin;
                q->extco2.MinQPP = q->extco2.MinQPB = q->extco2.MinQPI;
            }
            if (avctx->qmax >= 0) {
                q->extco2.MaxQPI = avctx->qmax > 51 ? 51 : avctx->qmax;
                q->extco2.MaxQPP = q->extco2.MaxQPB = q->extco2.MaxQPI;
            }
#endif
            q->extparam_internal[q->nb_extparam_internal++] = (mfxExtBuffer *)&q->extco2;
#endif

#if QSV_HAVE_MF
            if (QSV_RUNTIME_VERSION_ATLEAST(q->ver, 1, 25)) {
                q->extmfp.Header.BufferId     = MFX_EXTBUFF_MULTI_FRAME_PARAM;
                q->extmfp.Header.BufferSz     = sizeof(q->extmfp);

                q->extmfp.MFMode = q->mfmode;
                av_log(avctx,AV_LOG_VERBOSE,"MFMode:%d\n", q->extmfp.MFMode);
                q->extparam_internal[q->nb_extparam_internal++] = (mfxExtBuffer *)&q->extmfp;
            }
#endif
        }
#if QSV_HAVE_CO3
        q->extco3.Header.BufferId      = MFX_EXTBUFF_CODING_OPTION3;
        q->extco3.Header.BufferSz      = sizeof(q->extco3);
#if QSV_HAVE_GPB
        if (avctx->codec_id == AV_CODEC_ID_HEVC)
            q->extco3.GPB              = q->gpb ? MFX_CODINGOPTION_ON : MFX_CODINGOPTION_OFF;
#endif
        q->extparam_internal[q->nb_extparam_internal++] = (mfxExtBuffer *)&q->extco3;
#endif
    }

    if (!check_enc_param(avctx,q)) {
        av_log(avctx, AV_LOG_ERROR,
               "some encoding parameters are not supported by the QSV "
               "runtime. Please double check the input parameters.\n");
        return AVERROR(ENOSYS);
    }

    return 0;
}