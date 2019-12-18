#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ codec_id; int has_b_frames; scalar_t__ profile; scalar_t__ entropy; int dts_delta; int /*<<< orphan*/  session; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  ycbcr_matrix; int /*<<< orphan*/  transfer_function; int /*<<< orphan*/  allow_sw; scalar_t__ require_sw; int /*<<< orphan*/  get_param_set_func; } ;
typedef  TYPE_1__ VTEncContext ;
struct TYPE_16__ {scalar_t__ codec_id; scalar_t__ max_b_frames; scalar_t__ pix_fmt; int flags; TYPE_1__* priv_data; } ;
struct TYPE_14__ {int /*<<< orphan*/  kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder; int /*<<< orphan*/  kVTVideoEncoderSpecification_RequireHardwareAcceleratedVideoEncoder; int /*<<< orphan*/  CMVideoFormatDescriptionGetHEVCParameterSetAtIndex; } ;
typedef  int /*<<< orphan*/  CMVideoCodecType ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/ * CFNumberRef ;
typedef  int /*<<< orphan*/ * CFMutableDictionaryRef ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CODEC_FLAG_GLOBAL_HEADER ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PIX_FMT_VIDEOTOOLBOX ; 
 int /*<<< orphan*/ * CFDictionaryCreateMutable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFDictionarySetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMVideoFormatDescriptionGetH264ParameterSetAtIndex ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ H264_PROF_BASELINE ; 
 scalar_t__ VT_CABAC ; 
 scalar_t__ VT_ENTROPY_NOT_SET ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_12__ compat_keys ; 
 int create_cv_pixel_buffer_info (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_cm_codec_type (scalar_t__) ; 
 int /*<<< orphan*/  get_cv_color_primaries (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_cv_transfer_function (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_cv_ycbcr_matrix (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_vt_h264_profile_level (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_vt_hevc_profile_level (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFBooleanFalse ; 
 int /*<<< orphan*/  kCFBooleanTrue ; 
 int /*<<< orphan*/  kCFCopyStringDictionaryKeyCallBacks ; 
 int /*<<< orphan*/  kCFTypeDictionaryValueCallBacks ; 
 int vtenc_create_encoder (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vtenc_populate_extradata (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vtenc_configure_encoder(AVCodecContext *avctx)
{
    CFMutableDictionaryRef enc_info;
    CFMutableDictionaryRef pixel_buffer_info;
    CMVideoCodecType       codec_type;
    VTEncContext           *vtctx = avctx->priv_data;
    CFStringRef            profile_level;
    CFNumberRef            gamma_level = NULL;
    int                    status;

    codec_type = get_cm_codec_type(avctx->codec_id);
    if (!codec_type) {
        av_log(avctx, AV_LOG_ERROR, "Error: no mapping for AVCodecID %d\n", avctx->codec_id);
        return AVERROR(EINVAL);
    }

    vtctx->codec_id = avctx->codec_id;

    if (vtctx->codec_id == AV_CODEC_ID_H264) {
        vtctx->get_param_set_func = CMVideoFormatDescriptionGetH264ParameterSetAtIndex;

        vtctx->has_b_frames = avctx->max_b_frames > 0;
        if(vtctx->has_b_frames && vtctx->profile == H264_PROF_BASELINE){
            av_log(avctx, AV_LOG_WARNING, "Cannot use B-frames with baseline profile. Output will not contain B-frames.\n");
            vtctx->has_b_frames = false;
        }

        if (vtctx->entropy == VT_CABAC && vtctx->profile == H264_PROF_BASELINE) {
            av_log(avctx, AV_LOG_WARNING, "CABAC entropy requires 'main' or 'high' profile, but baseline was requested. Encode will not use CABAC entropy.\n");
            vtctx->entropy = VT_ENTROPY_NOT_SET;
        }

        if (!get_vt_h264_profile_level(avctx, &profile_level)) return AVERROR(EINVAL);
    } else {
        vtctx->get_param_set_func = compat_keys.CMVideoFormatDescriptionGetHEVCParameterSetAtIndex;
        if (!vtctx->get_param_set_func) return AVERROR(EINVAL);
        if (!get_vt_hevc_profile_level(avctx, &profile_level)) return AVERROR(EINVAL);
    }

    enc_info = CFDictionaryCreateMutable(
        kCFAllocatorDefault,
        20,
        &kCFCopyStringDictionaryKeyCallBacks,
        &kCFTypeDictionaryValueCallBacks
    );

    if (!enc_info) return AVERROR(ENOMEM);

#if !TARGET_OS_IPHONE
    if(vtctx->require_sw) {
        CFDictionarySetValue(enc_info,
                             compat_keys.kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder,
                             kCFBooleanFalse);
    } else if (!vtctx->allow_sw) {
        CFDictionarySetValue(enc_info,
                             compat_keys.kVTVideoEncoderSpecification_RequireHardwareAcceleratedVideoEncoder,
                             kCFBooleanTrue);
    } else {
        CFDictionarySetValue(enc_info,
                             compat_keys.kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder,
                             kCFBooleanTrue);
    }
#endif

    if (avctx->pix_fmt != AV_PIX_FMT_VIDEOTOOLBOX) {
        status = create_cv_pixel_buffer_info(avctx, &pixel_buffer_info);
        if (status)
            goto init_cleanup;
    } else {
        pixel_buffer_info = NULL;
    }

    vtctx->dts_delta = vtctx->has_b_frames ? -1 : 0;

    get_cv_transfer_function(avctx, &vtctx->transfer_function, &gamma_level);
    get_cv_ycbcr_matrix(avctx, &vtctx->ycbcr_matrix);
    get_cv_color_primaries(avctx, &vtctx->color_primaries);


    if (avctx->flags & AV_CODEC_FLAG_GLOBAL_HEADER) {
        status = vtenc_populate_extradata(avctx,
                                          codec_type,
                                          profile_level,
                                          gamma_level,
                                          enc_info,
                                          pixel_buffer_info);
        if (status)
            goto init_cleanup;
    }

    status = vtenc_create_encoder(avctx,
                                  codec_type,
                                  profile_level,
                                  gamma_level,
                                  enc_info,
                                  pixel_buffer_info,
                                  &vtctx->session);

init_cleanup:
    if (gamma_level)
        CFRelease(gamma_level);

    if (pixel_buffer_info)
        CFRelease(pixel_buffer_info);

    CFRelease(enc_info);

    return status;
}