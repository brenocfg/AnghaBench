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
typedef  int uint32_t ;

/* Variables and functions */
#define  HB_VCODEC_FFMPEG_NVENC_H264 137 
#define  HB_VCODEC_FFMPEG_NVENC_H265 136 
#define  HB_VCODEC_FFMPEG_VP8 135 
#define  HB_VCODEC_FFMPEG_VP9 134 
 int HB_VCODEC_QSV_MASK ; 
#define  HB_VCODEC_X264_10BIT 133 
#define  HB_VCODEC_X264_8BIT 132 
#define  HB_VCODEC_X265_10BIT 131 
#define  HB_VCODEC_X265_12BIT 130 
#define  HB_VCODEC_X265_16BIT 129 
#define  HB_VCODEC_X265_8BIT 128 
 char const* hb_qsv_video_quality_get_name (int) ; 

const char* hb_video_quality_get_name(uint32_t codec)
{
#if HB_PROJECT_FEATURE_QSV
    if (codec & HB_VCODEC_QSV_MASK)
    {
        return hb_qsv_video_quality_get_name(codec);
    }
#endif

    switch (codec)
    {
        case HB_VCODEC_X264_8BIT:
        case HB_VCODEC_X264_10BIT:
        case HB_VCODEC_X265_8BIT:
        case HB_VCODEC_X265_10BIT:
        case HB_VCODEC_X265_12BIT:
        case HB_VCODEC_X265_16BIT:
            return "RF";

        case HB_VCODEC_FFMPEG_VP8:
        case HB_VCODEC_FFMPEG_VP9:
        case HB_VCODEC_FFMPEG_NVENC_H264:
        case HB_VCODEC_FFMPEG_NVENC_H265:
            return "CQ";

        default:
            return "QP";
    }
}