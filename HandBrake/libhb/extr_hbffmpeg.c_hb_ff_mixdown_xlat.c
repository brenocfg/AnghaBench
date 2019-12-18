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
 int AV_CH_LAYOUT_5POINT1 ; 
 int AV_CH_LAYOUT_5POINT1_BACK ; 
 int AV_CH_LAYOUT_6POINT1 ; 
 int AV_CH_LAYOUT_7POINT1 ; 
 int AV_CH_LAYOUT_MONO ; 
 int AV_CH_LAYOUT_STEREO ; 
 int AV_MATRIX_ENCODING_DOLBY ; 
 int AV_MATRIX_ENCODING_DPLII ; 
 int AV_MATRIX_ENCODING_NONE ; 
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
 int /*<<< orphan*/  hb_log (char*,int) ; 

uint64_t hb_ff_mixdown_xlat(int hb_mixdown, int *downmix_mode)
{
    uint64_t ff_layout = 0;
    int mode = AV_MATRIX_ENCODING_NONE;
    switch (hb_mixdown)
    {
        // Passthru
        case HB_AMIXDOWN_NONE:
            break;

        case HB_AMIXDOWN_MONO:
        case HB_AMIXDOWN_LEFT:
        case HB_AMIXDOWN_RIGHT:
            ff_layout = AV_CH_LAYOUT_MONO;
            break;

        case HB_AMIXDOWN_DOLBY:
            ff_layout = AV_CH_LAYOUT_STEREO;
            mode = AV_MATRIX_ENCODING_DOLBY;
            break;

        case HB_AMIXDOWN_DOLBYPLII:
            ff_layout = AV_CH_LAYOUT_STEREO;
            mode = AV_MATRIX_ENCODING_DPLII;
            break;

        case HB_AMIXDOWN_STEREO:
            ff_layout = AV_CH_LAYOUT_STEREO;
            break;

        case HB_AMIXDOWN_5POINT1:
            ff_layout = AV_CH_LAYOUT_5POINT1;
            break;

        case HB_AMIXDOWN_6POINT1:
            ff_layout = AV_CH_LAYOUT_6POINT1;
            break;

        case HB_AMIXDOWN_7POINT1:
            ff_layout = AV_CH_LAYOUT_7POINT1;
            break;

        case HB_AMIXDOWN_5_2_LFE:
            ff_layout = (AV_CH_LAYOUT_5POINT1_BACK|
                         AV_CH_FRONT_LEFT_OF_CENTER|
                         AV_CH_FRONT_RIGHT_OF_CENTER);
            break;

        default:
            ff_layout = AV_CH_LAYOUT_STEREO;
            hb_log("hb_ff_mixdown_xlat: unsupported mixdown %d", hb_mixdown);
            break;
    }
    if (downmix_mode != NULL)
        *downmix_mode = mode;
    return ff_layout;
}