#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_8__ {scalar_t__ codec_id; scalar_t__ entropy; int /*<<< orphan*/  session; scalar_t__ realtime; int /*<<< orphan*/  has_b_frames; scalar_t__ color_primaries; scalar_t__ ycbcr_matrix; scalar_t__ transfer_function; scalar_t__ frames_after; scalar_t__ frames_before; int /*<<< orphan*/  allow_sw; } ;
typedef  TYPE_1__ VTEncContext ;
typedef  int /*<<< orphan*/  VTCompressionSessionRef ;
struct TYPE_11__ {int /*<<< orphan*/  kVTCompressionPropertyKey_RealTime; int /*<<< orphan*/  kVTCompressionPropertyKey_H264EntropyMode; scalar_t__ kVTH264EntropyMode_CAVLC; scalar_t__ kVTH264EntropyMode_CABAC; } ;
struct TYPE_9__ {int num; int den; } ;
struct TYPE_10__ {int bit_rate; int rc_max_rate; scalar_t__ gop_size; TYPE_2__ sample_aspect_ratio; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* priv_data; } ;
typedef  int SInt32 ;
typedef  int /*<<< orphan*/  CMVideoCodecType ;
typedef  scalar_t__ CFStringRef ;
typedef  scalar_t__ CFNumberRef ;
typedef  scalar_t__ CFMutableDictionaryRef ;
typedef  int /*<<< orphan*/  CFDictionaryRef ;
typedef  scalar_t__ CFArrayRef ;
typedef  TYPE_2__ AVRational ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ CFArrayCreate (int /*<<< orphan*/ ,void const**,int,int /*<<< orphan*/ *) ; 
 scalar_t__ CFDictionaryCreateMutable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFDictionarySetValue (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ CFNumberCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CFRelease (scalar_t__) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int VTCompressionSessionCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int VTCompressionSessionPrepareToEncodeFrames (int /*<<< orphan*/ ) ; 
 int VTSessionSetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ VT_CABAC ; 
 scalar_t__ VT_ENTROPY_NOT_SET ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_reduce (int*,int*,int,int,int) ; 
 TYPE_5__ compat_keys ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 scalar_t__ kCFBooleanFalse ; 
 scalar_t__ kCFBooleanTrue ; 
 int /*<<< orphan*/  kCFCopyStringDictionaryKeyCallBacks ; 
 int /*<<< orphan*/  kCFNumberIntType ; 
 int /*<<< orphan*/  kCFNumberSInt32Type ; 
 int /*<<< orphan*/  kCFNumberSInt64Type ; 
 int /*<<< orphan*/  kCFTypeArrayCallBacks ; 
 int /*<<< orphan*/  kCFTypeDictionaryValueCallBacks ; 
 int /*<<< orphan*/  kCMFormatDescriptionKey_PixelAspectRatioHorizontalSpacing ; 
 int /*<<< orphan*/  kCMFormatDescriptionKey_PixelAspectRatioVerticalSpacing ; 
 int /*<<< orphan*/  kCVImageBufferGammaLevelKey ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_AllowFrameReordering ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_AverageBitRate ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_ColorPrimaries ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_DataRateLimits ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_MaxKeyFrameInterval ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_MoreFramesAfterEnd ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_MoreFramesBeforeStart ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_PixelAspectRatio ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_ProfileLevel ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_TransferFunction ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_YCbCrMatrix ; 
 int kVTPropertyNotSupportedErr ; 
 int /*<<< orphan*/  vtenc_output_callback ; 

__attribute__((used)) static int vtenc_create_encoder(AVCodecContext   *avctx,
                                CMVideoCodecType codec_type,
                                CFStringRef      profile_level,
                                CFNumberRef      gamma_level,
                                CFDictionaryRef  enc_info,
                                CFDictionaryRef  pixel_buffer_info,
                                VTCompressionSessionRef *session)
{
    VTEncContext *vtctx = avctx->priv_data;
    SInt32       bit_rate = avctx->bit_rate;
    SInt32       max_rate = avctx->rc_max_rate;
    CFNumberRef  bit_rate_num;
    CFNumberRef  bytes_per_second;
    CFNumberRef  one_second;
    CFArrayRef   data_rate_limits;
    int64_t      bytes_per_second_value = 0;
    int64_t      one_second_value = 0;
    void         *nums[2];

    int status = VTCompressionSessionCreate(kCFAllocatorDefault,
                                            avctx->width,
                                            avctx->height,
                                            codec_type,
                                            enc_info,
                                            pixel_buffer_info,
                                            kCFAllocatorDefault,
                                            vtenc_output_callback,
                                            avctx,
                                            session);

    if (status || !vtctx->session) {
        av_log(avctx, AV_LOG_ERROR, "Error: cannot create compression session: %d\n", status);

#if !TARGET_OS_IPHONE
        if (!vtctx->allow_sw) {
            av_log(avctx, AV_LOG_ERROR, "Try -allow_sw 1. The hardware encoder may be busy, or not supported.\n");
        }
#endif

        return AVERROR_EXTERNAL;
    }

    bit_rate_num = CFNumberCreate(kCFAllocatorDefault,
                                  kCFNumberSInt32Type,
                                  &bit_rate);
    if (!bit_rate_num) return AVERROR(ENOMEM);

    status = VTSessionSetProperty(vtctx->session,
                                  kVTCompressionPropertyKey_AverageBitRate,
                                  bit_rate_num);
    CFRelease(bit_rate_num);

    if (status) {
        av_log(avctx, AV_LOG_ERROR, "Error setting bitrate property: %d\n", status);
        return AVERROR_EXTERNAL;
    }

    if (vtctx->codec_id == AV_CODEC_ID_H264 && max_rate > 0) {
        // kVTCompressionPropertyKey_DataRateLimits is not available for HEVC
        bytes_per_second_value = max_rate >> 3;
        bytes_per_second = CFNumberCreate(kCFAllocatorDefault,
                                          kCFNumberSInt64Type,
                                          &bytes_per_second_value);
        if (!bytes_per_second) {
            return AVERROR(ENOMEM);
        }
        one_second_value = 1;
        one_second = CFNumberCreate(kCFAllocatorDefault,
                                    kCFNumberSInt64Type,
                                    &one_second_value);
        if (!one_second) {
            CFRelease(bytes_per_second);
            return AVERROR(ENOMEM);
        }
        nums[0] = (void *)bytes_per_second;
        nums[1] = (void *)one_second;
        data_rate_limits = CFArrayCreate(kCFAllocatorDefault,
                                         (const void **)nums,
                                         2,
                                         &kCFTypeArrayCallBacks);

        if (!data_rate_limits) {
            CFRelease(bytes_per_second);
            CFRelease(one_second);
            return AVERROR(ENOMEM);
        }
        status = VTSessionSetProperty(vtctx->session,
                                      kVTCompressionPropertyKey_DataRateLimits,
                                      data_rate_limits);

        CFRelease(bytes_per_second);
        CFRelease(one_second);
        CFRelease(data_rate_limits);

        if (status) {
            av_log(avctx, AV_LOG_ERROR, "Error setting max bitrate property: %d\n", status);
            return AVERROR_EXTERNAL;
        }
    }

    if (vtctx->codec_id == AV_CODEC_ID_H264) {
        // kVTCompressionPropertyKey_ProfileLevel is not available for HEVC
        if (profile_level) {
            status = VTSessionSetProperty(vtctx->session,
                                        kVTCompressionPropertyKey_ProfileLevel,
                                        profile_level);
            if (status) {
                av_log(avctx, AV_LOG_ERROR, "Error setting profile/level property: %d. Output will be encoded using a supported profile/level combination.\n", status);
            }
        }
    }

    if (avctx->gop_size > 0) {
        CFNumberRef interval = CFNumberCreate(kCFAllocatorDefault,
                                              kCFNumberIntType,
                                              &avctx->gop_size);
        if (!interval) {
            return AVERROR(ENOMEM);
        }

        status = VTSessionSetProperty(vtctx->session,
                                      kVTCompressionPropertyKey_MaxKeyFrameInterval,
                                      interval);
        CFRelease(interval);

        if (status) {
            av_log(avctx, AV_LOG_ERROR, "Error setting 'max key-frame interval' property: %d\n", status);
            return AVERROR_EXTERNAL;
        }
    }

    if (vtctx->frames_before) {
        status = VTSessionSetProperty(vtctx->session,
                                      kVTCompressionPropertyKey_MoreFramesBeforeStart,
                                      kCFBooleanTrue);

        if (status == kVTPropertyNotSupportedErr) {
            av_log(avctx, AV_LOG_WARNING, "frames_before property is not supported on this device. Ignoring.\n");
        } else if (status) {
            av_log(avctx, AV_LOG_ERROR, "Error setting frames_before property: %d\n", status);
        }
    }

    if (vtctx->frames_after) {
        status = VTSessionSetProperty(vtctx->session,
                                      kVTCompressionPropertyKey_MoreFramesAfterEnd,
                                      kCFBooleanTrue);

        if (status == kVTPropertyNotSupportedErr) {
            av_log(avctx, AV_LOG_WARNING, "frames_after property is not supported on this device. Ignoring.\n");
        } else if (status) {
            av_log(avctx, AV_LOG_ERROR, "Error setting frames_after property: %d\n", status);
        }
    }

    if (avctx->sample_aspect_ratio.num != 0) {
        CFNumberRef num;
        CFNumberRef den;
        CFMutableDictionaryRef par;
        AVRational *avpar = &avctx->sample_aspect_ratio;

        av_reduce(&avpar->num, &avpar->den,
                   avpar->num,  avpar->den,
                  0xFFFFFFFF);

        num = CFNumberCreate(kCFAllocatorDefault,
                             kCFNumberIntType,
                             &avpar->num);

        den = CFNumberCreate(kCFAllocatorDefault,
                             kCFNumberIntType,
                             &avpar->den);



        par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                        2,
                                        &kCFCopyStringDictionaryKeyCallBacks,
                                        &kCFTypeDictionaryValueCallBacks);

        if (!par || !num || !den) {
            if (par) CFRelease(par);
            if (num) CFRelease(num);
            if (den) CFRelease(den);

            return AVERROR(ENOMEM);
        }

        CFDictionarySetValue(
            par,
            kCMFormatDescriptionKey_PixelAspectRatioHorizontalSpacing,
            num);

        CFDictionarySetValue(
            par,
            kCMFormatDescriptionKey_PixelAspectRatioVerticalSpacing,
            den);

        status = VTSessionSetProperty(vtctx->session,
                                      kVTCompressionPropertyKey_PixelAspectRatio,
                                      par);

        CFRelease(par);
        CFRelease(num);
        CFRelease(den);

        if (status) {
            av_log(avctx,
                   AV_LOG_ERROR,
                   "Error setting pixel aspect ratio to %d:%d: %d.\n",
                   avctx->sample_aspect_ratio.num,
                   avctx->sample_aspect_ratio.den,
                   status);

            return AVERROR_EXTERNAL;
        }
    }


    if (vtctx->transfer_function) {
        status = VTSessionSetProperty(vtctx->session,
                                      kVTCompressionPropertyKey_TransferFunction,
                                      vtctx->transfer_function);

        if (status) {
            av_log(avctx, AV_LOG_WARNING, "Could not set transfer function: %d\n", status);
        }
    }


    if (vtctx->ycbcr_matrix) {
        status = VTSessionSetProperty(vtctx->session,
                                      kVTCompressionPropertyKey_YCbCrMatrix,
                                      vtctx->ycbcr_matrix);

        if (status) {
            av_log(avctx, AV_LOG_WARNING, "Could not set ycbcr matrix: %d\n", status);
        }
    }


    if (vtctx->color_primaries) {
        status = VTSessionSetProperty(vtctx->session,
                                      kVTCompressionPropertyKey_ColorPrimaries,
                                      vtctx->color_primaries);

        if (status) {
            av_log(avctx, AV_LOG_WARNING, "Could not set color primaries: %d\n", status);
        }
    }

    if (gamma_level) {
        status = VTSessionSetProperty(vtctx->session,
                                      kCVImageBufferGammaLevelKey,
                                      gamma_level);

        if (status) {
            av_log(avctx, AV_LOG_WARNING, "Could not set gamma level: %d\n", status);
        }
    }

    if (!vtctx->has_b_frames) {
        status = VTSessionSetProperty(vtctx->session,
                                      kVTCompressionPropertyKey_AllowFrameReordering,
                                      kCFBooleanFalse);

        if (status) {
            av_log(avctx, AV_LOG_ERROR, "Error setting 'allow frame reordering' property: %d\n", status);
            return AVERROR_EXTERNAL;
        }
    }

    if (vtctx->entropy != VT_ENTROPY_NOT_SET) {
        CFStringRef entropy = vtctx->entropy == VT_CABAC ?
                                compat_keys.kVTH264EntropyMode_CABAC:
                                compat_keys.kVTH264EntropyMode_CAVLC;

        status = VTSessionSetProperty(vtctx->session,
                                      compat_keys.kVTCompressionPropertyKey_H264EntropyMode,
                                      entropy);

        if (status) {
            av_log(avctx, AV_LOG_ERROR, "Error setting entropy property: %d\n", status);
        }
    }

    if (vtctx->realtime) {
        status = VTSessionSetProperty(vtctx->session,
                                      compat_keys.kVTCompressionPropertyKey_RealTime,
                                      kCFBooleanTrue);

        if (status) {
            av_log(avctx, AV_LOG_ERROR, "Error setting realtime property: %d\n", status);
        }
    }

    status = VTCompressionSessionPrepareToEncodeFrames(vtctx->session);
    if (status) {
        av_log(avctx, AV_LOG_ERROR, "Error: cannot prepare encoder: %d\n", status);
        return AVERROR_EXTERNAL;
    }

    return 0;
}