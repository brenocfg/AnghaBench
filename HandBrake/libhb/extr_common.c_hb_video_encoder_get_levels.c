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
 char const* const* hb_h264_level_names ; 
 char const* const* hb_h265_level_names ; 
 char const* const* hb_qsv_level_get_names (int) ; 
 char const* const* hb_vce_h264_level_names ; 
 char const* const* hb_vt_h265_level_names ; 

const char* const* hb_video_encoder_get_levels(int encoder)
{
#if HB_PROJECT_FEATURE_QSV
    if (encoder & HB_VCODEC_QSV_MASK)
    {
        return hb_qsv_level_get_names(encoder);
    }
#endif

    switch (encoder)
    {
        case HB_VCODEC_X264_8BIT:
        case HB_VCODEC_X264_10BIT:
        case HB_VCODEC_FFMPEG_NVENC_H264:
        case HB_VCODEC_FFMPEG_VT_H264:
            return hb_h264_level_names;

#if HB_PROJECT_FEATURE_VCE
     case HB_VCODEC_FFMPEG_VCE_H264:
            return hb_vce_h264_level_names; // Not quite the same as x264
#endif

        case HB_VCODEC_X265_8BIT:
        case HB_VCODEC_X265_10BIT:
        case HB_VCODEC_X265_12BIT:
        case HB_VCODEC_X265_16BIT:
        case HB_VCODEC_FFMPEG_NVENC_H265:
        case HB_VCODEC_FFMPEG_VCE_H265:
            return hb_h265_level_names;

#ifdef __APPLE__
        case HB_VCODEC_FFMPEG_VT_H265:
            return hb_vt_h265_level_names;
#endif

        default:
            return NULL;
    }
}