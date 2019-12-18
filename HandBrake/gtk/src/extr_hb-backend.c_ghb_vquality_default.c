#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int gint ;

/* Variables and functions */
#define  HB_VCODEC_FFMPEG_MPEG2 136 
#define  HB_VCODEC_FFMPEG_MPEG4 135 
#define  HB_VCODEC_THEORA 134 
#define  HB_VCODEC_X264_10BIT 133 
#define  HB_VCODEC_X264_8BIT 132 
#define  HB_VCODEC_X265_10BIT 131 
#define  HB_VCODEC_X265_12BIT 130 
#define  HB_VCODEC_X265_16BIT 129 
#define  HB_VCODEC_X265_8BIT 128 
 int ghb_settings_video_encoder_codec (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hb_video_quality_get_limits (int,float*,float*,float*,int*) ; 

float
ghb_vquality_default(signal_user_data_t *ud)
{
    float quality;
    gint vcodec;
    vcodec = ghb_settings_video_encoder_codec(ud->settings, "VideoEncoder");

    switch (vcodec)
    {
    case HB_VCODEC_X265_8BIT:
    case HB_VCODEC_X265_10BIT:
    case HB_VCODEC_X265_12BIT:
    case HB_VCODEC_X265_16BIT:
    case HB_VCODEC_X264_8BIT:
    case HB_VCODEC_X264_10BIT:
        return 20;
    case HB_VCODEC_THEORA:
        return 45;
    case HB_VCODEC_FFMPEG_MPEG2:
    case HB_VCODEC_FFMPEG_MPEG4:
        return 3;
    default:
    {
        float min, max, step;
        int direction;

        hb_video_quality_get_limits(vcodec, &min, &max, &step, &direction);
        // Pick something that is 70% of max
        // Probably too low for some and too high for others...
        quality = (max - min) * 0.7;
        if (direction)
            quality = max - quality;
    }
    }
    return quality;
}