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
#define  HB_VCODEC_QSV_H265_10BIT 132 
#define  HB_VCODEC_X264_10BIT 131 
#define  HB_VCODEC_X265_10BIT 130 
#define  HB_VCODEC_X265_12BIT 129 
#define  HB_VCODEC_X265_16BIT 128 

int hb_video_encoder_get_depth(int encoder)
{
    switch (encoder)
    {
#if HB_PROJECT_FEATURE_QSV
        case HB_VCODEC_QSV_H265_10BIT:
#endif
        case HB_VCODEC_X264_10BIT:
        case HB_VCODEC_X265_10BIT:
            return 10;
        case HB_VCODEC_X265_12BIT:
            return 12;
        case HB_VCODEC_X265_16BIT:
            return 16;
        default:
            return 8;
    }
}