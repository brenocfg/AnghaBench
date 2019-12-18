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
#define  HB_VCODEC_FFMPEG_MPEG2 142 
#define  HB_VCODEC_FFMPEG_MPEG4 141 
#define  HB_VCODEC_FFMPEG_NVENC_H264 140 
#define  HB_VCODEC_FFMPEG_NVENC_H265 139 
#define  HB_VCODEC_FFMPEG_VP8 138 
#define  HB_VCODEC_FFMPEG_VP9 137 
#define  HB_VCODEC_FFMPEG_VT_H264 136 
#define  HB_VCODEC_FFMPEG_VT_H265 135 
 int HB_VCODEC_QSV_MASK ; 
#define  HB_VCODEC_THEORA 134 
#define  HB_VCODEC_X264_10BIT 133 
#define  HB_VCODEC_X264_8BIT 132 
#define  HB_VCODEC_X265_10BIT 131 
#define  HB_VCODEC_X265_12BIT 130 
#define  HB_VCODEC_X265_16BIT 129 
#define  HB_VCODEC_X265_8BIT 128 
 void hb_qsv_video_quality_get_limits (int,float*,float*,float*,int*) ; 

void hb_video_quality_get_limits(uint32_t codec, float *low, float *high,
                                 float *granularity, int *direction)
{
#if HB_PROJECT_FEATURE_QSV
    if (codec & HB_VCODEC_QSV_MASK)
    {
        return hb_qsv_video_quality_get_limits(codec, low, high, granularity,
                                               direction);
    }
#endif

    switch (codec)
    {
        /*
         * H.264/H.265: *low
         * = 51 - (QP_MAX_SPEC)
         * = 51 - (51 + QP_BD_OFFSET)
         * =  0 - (QP_BD_OFFSET)
         * =  0 - (6*(BIT_DEPTH-8))     (libx264)
         * =  0 - (6*(X265_DEPTH-8))    (libx265)
         */
        case HB_VCODEC_X264_8BIT:
        case HB_VCODEC_X265_8BIT:
        case HB_VCODEC_FFMPEG_NVENC_H264:
        case HB_VCODEC_FFMPEG_NVENC_H265:
            *direction   = 1;
            *granularity = 0.1;
            *low         = 0.;
            *high        = 51.;
            break;
        case HB_VCODEC_X264_10BIT:
        case HB_VCODEC_X265_10BIT:
            *direction   = 1;
            *granularity = 0.1;
            *low         = -12.;
            *high        = 51.;
            break;
        case HB_VCODEC_X265_12BIT:
            *direction   = 1;
            *granularity = 0.1;
            *low         = -24.;
            *high        = 51.;
            break;
        case HB_VCODEC_X265_16BIT:
            *direction   = 1;
            *granularity = 0.1;
            *low         = -48.;
            *high        = 51.;
            break;

        case HB_VCODEC_THEORA:
            *direction   = 0;
            *granularity = 1.;
            *low         = 0.;
            *high        = 63.;
            break;

        case HB_VCODEC_FFMPEG_VP8:
        case HB_VCODEC_FFMPEG_VP9:
            *direction   = 1;
            *granularity = 1.;
            *low         = 0.;
            *high        = 63.;
            break;

        case HB_VCODEC_FFMPEG_VT_H264:
        case HB_VCODEC_FFMPEG_VT_H265:
            *direction   = 1;
            *granularity = 0.1;
            *low         = 0.;
            *high        = 0.;
            break;

        case HB_VCODEC_FFMPEG_MPEG2:
        case HB_VCODEC_FFMPEG_MPEG4:
        default:
            *direction   = 1;
            *granularity = 1.;
            *low         = 1.;
            *high        = 31.;
            break;
    }
}