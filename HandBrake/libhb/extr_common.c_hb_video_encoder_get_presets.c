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
 int HB_VCODEC_FFMPEG_MASK ; 
 int HB_VCODEC_QSV_MASK ; 
#define  HB_VCODEC_X264_10BIT 133 
#define  HB_VCODEC_X264_8BIT 132 
#define  HB_VCODEC_X265_10BIT 131 
#define  HB_VCODEC_X265_12BIT 130 
#define  HB_VCODEC_X265_16BIT 129 
#define  HB_VCODEC_X265_8BIT 128 
 char const* const* hb_av_preset_get_names (int) ; 
 char const* const* hb_qsv_preset_get_names () ; 
 char const* const* x264_preset_names ; 
 char const* const* x265_preset_names ; 

const char* const* hb_video_encoder_get_presets(int encoder)
{
#if HB_PROJECT_FEATURE_QSV
    if (encoder & HB_VCODEC_QSV_MASK)
    {
        return hb_qsv_preset_get_names();
    }
#endif

    if (encoder & HB_VCODEC_FFMPEG_MASK)
    {
        return hb_av_preset_get_names(encoder);
    }

    switch (encoder)
    {
        case HB_VCODEC_X264_8BIT:
        case HB_VCODEC_X264_10BIT:
            return x264_preset_names;

#if HB_PROJECT_FEATURE_X265
        case HB_VCODEC_X265_8BIT:
        case HB_VCODEC_X265_10BIT:
        case HB_VCODEC_X265_12BIT:
        case HB_VCODEC_X265_16BIT:
            return x265_preset_names;
#endif
        default:
            return NULL;
    }
}