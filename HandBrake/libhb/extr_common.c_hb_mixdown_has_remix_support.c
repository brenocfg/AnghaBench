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
typedef  int uint64_t ;

/* Variables and functions */
 int AV_CH_FRONT_LEFT_OF_CENTER ; 
 int AV_CH_FRONT_RIGHT_OF_CENTER ; 
 int AV_CH_LAYOUT_2_1 ; 
 int AV_CH_LAYOUT_2_2 ; 
 int AV_CH_LAYOUT_6POINT0 ; 
 int AV_CH_LAYOUT_7POINT0 ; 
 int AV_CH_LAYOUT_HEXAGONAL ; 
 int AV_CH_LAYOUT_QUAD ; 
 int AV_CH_LAYOUT_STEREO ; 
 int AV_CH_LAYOUT_STEREO_DOWNMIX ; 
 int AV_CH_LAYOUT_SURROUND ; 
#define  HB_AMIXDOWN_5POINT1 138 
#define  HB_AMIXDOWN_5_2_LFE 137 
#define  HB_AMIXDOWN_6POINT1 136 
#define  HB_AMIXDOWN_7POINT1 135 
#define  HB_AMIXDOWN_DOLBY 134 
#define  HB_AMIXDOWN_DOLBYPLII 133 
#define  HB_AMIXDOWN_LEFT 132 
#define  HB_AMIXDOWN_MONO 131 
#define  HB_AMIXDOWN_NONE 130 
#define  HB_AMIXDOWN_RIGHT 129 
#define  HB_AMIXDOWN_STEREO 128 
 int av_get_channel_layout_nb_channels (int) ; 

int hb_mixdown_has_remix_support(int mixdown, uint64_t layout)
{
    /*
     * Where there isn't a source (e.g. audio defaults panel), we have no input
     * layout; assume remix support, as the mixdown will be sanitized later on.
     */
    if (!layout)
    {
        return 1;
    }
    switch (mixdown)
    {
        // stereo + front left/right of center
        case HB_AMIXDOWN_5_2_LFE:
            return ((layout & AV_CH_FRONT_LEFT_OF_CENTER) &&
                    (layout & AV_CH_FRONT_RIGHT_OF_CENTER) &&
                    (layout & AV_CH_LAYOUT_STEREO) == AV_CH_LAYOUT_STEREO);

        // 7.0 or better
        case HB_AMIXDOWN_7POINT1:
            return ((layout & AV_CH_LAYOUT_7POINT0) == AV_CH_LAYOUT_7POINT0);

        // 6.0 or better
        case HB_AMIXDOWN_6POINT1:
            return ((layout & AV_CH_LAYOUT_7POINT0) == AV_CH_LAYOUT_7POINT0 ||
                    (layout & AV_CH_LAYOUT_6POINT0) == AV_CH_LAYOUT_6POINT0 ||
                    (layout & AV_CH_LAYOUT_HEXAGONAL) == AV_CH_LAYOUT_HEXAGONAL);

        // stereo + either of front center, side or back left/right, back center
        case HB_AMIXDOWN_5POINT1:
            return ((layout & AV_CH_LAYOUT_2_1) == AV_CH_LAYOUT_2_1 ||
                    (layout & AV_CH_LAYOUT_2_2) == AV_CH_LAYOUT_2_2 ||
                    (layout & AV_CH_LAYOUT_QUAD) == AV_CH_LAYOUT_QUAD ||
                    (layout & AV_CH_LAYOUT_SURROUND) == AV_CH_LAYOUT_SURROUND);

        // stereo + either of side or back left/right, back center
        // also, allow Dolby Surround output if the input is already Dolby
        case HB_AMIXDOWN_DOLBY:
        case HB_AMIXDOWN_DOLBYPLII:
            return ((layout & AV_CH_LAYOUT_2_1) == AV_CH_LAYOUT_2_1 ||
                    (layout & AV_CH_LAYOUT_2_2) == AV_CH_LAYOUT_2_2 ||
                    (layout & AV_CH_LAYOUT_QUAD) == AV_CH_LAYOUT_QUAD ||
                    (layout == AV_CH_LAYOUT_STEREO_DOWNMIX &&
                     mixdown == HB_AMIXDOWN_DOLBY));

        // more than 1 channel
        case HB_AMIXDOWN_STEREO:
            return (av_get_channel_layout_nb_channels(layout) > 1);

        // regular stereo (not Dolby)
        case HB_AMIXDOWN_LEFT:
        case HB_AMIXDOWN_RIGHT:
            return (layout & AV_CH_LAYOUT_STEREO);

        // mono remix always supported
        // HB_AMIXDOWN_NONE always supported (for Passthru)
        case HB_AMIXDOWN_MONO:
        case HB_AMIXDOWN_NONE:
            return 1;

        // unknown mixdown, should never happen
        default:
            return 0;
    }
}