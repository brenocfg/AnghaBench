#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  HB_VCODEC_FFMPEG_NVENC_H264 139 
#define  HB_VCODEC_FFMPEG_NVENC_H265 138 
#define  HB_VCODEC_FFMPEG_VCE_H264 137 
#define  HB_VCODEC_FFMPEG_VCE_H265 136 
#define  HB_VCODEC_FFMPEG_VT_H264 135 
#define  HB_VCODEC_FFMPEG_VT_H265 134 
 int HB_VCODEC_QSV_MASK ; 
#define  HB_VCODEC_X264_10BIT 133 
#define  HB_VCODEC_X264_8BIT 132 
#define  HB_VCODEC_X265_10BIT 131 
#define  HB_VCODEC_X265_12BIT 130 
#define  HB_VCODEC_X265_16BIT 129 
#define  HB_VCODEC_X265_8BIT 128 
 char const* const* hb_av_profile_get_names (int) ; 
 char const* const* hb_h264_profile_names_10bit ; 
 char const* const* hb_h264_profile_names_8bit ; 
 char const* const* hb_h265_profile_names_10bit ; 
 char const* const* hb_h265_profile_names_12bit ; 
 char const* const* hb_h265_profile_names_16bit ; 
 char const* const* hb_h265_profile_names_8bit ; 
 char const* const* hb_qsv_profile_get_names (int) ; 
 char const* const* hb_vce_h264_profile_names ; 
 char const* const* hb_vce_h265_profile_names ; 

const char* const* hb_video_encoder_get_profiles(int encoder)
{
#if HB_PROJECT_FEATURE_QSV
    if (encoder & HB_VCODEC_QSV_MASK)
    {
        return hb_qsv_profile_get_names(encoder);
    }
#endif

    switch (encoder)
    {
        case HB_VCODEC_X264_8BIT:
            return hb_h264_profile_names_8bit;
        case HB_VCODEC_X264_10BIT:
            return hb_h264_profile_names_10bit;

        case HB_VCODEC_X265_8BIT:
            return hb_h265_profile_names_8bit;
        case HB_VCODEC_X265_10BIT:
            return hb_h265_profile_names_10bit;
        case HB_VCODEC_X265_12BIT:
            return hb_h265_profile_names_12bit;
        case HB_VCODEC_X265_16BIT:
            return hb_h265_profile_names_16bit;

#if HB_PROJECT_FEATURE_VCE
        case HB_VCODEC_FFMPEG_VCE_H264:
            return hb_vce_h264_profile_names;
        case HB_VCODEC_FFMPEG_VCE_H265:
            return hb_vce_h265_profile_names;
#endif

        case HB_VCODEC_FFMPEG_NVENC_H264:
        case HB_VCODEC_FFMPEG_NVENC_H265:
        case HB_VCODEC_FFMPEG_VT_H264:
        case HB_VCODEC_FFMPEG_VT_H265:
            return hb_av_profile_get_names(encoder);
        default:
            return NULL;
    }
}