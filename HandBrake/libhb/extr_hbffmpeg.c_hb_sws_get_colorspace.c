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
#define  HB_COLR_MAT_BT2020_CL 132 
#define  HB_COLR_MAT_BT2020_NCL 131 
#define  HB_COLR_MAT_BT709 130 
#define  HB_COLR_MAT_SMPTE170M 129 
#define  HB_COLR_MAT_SMPTE240M 128 
 int SWS_CS_BT2020 ; 
 int SWS_CS_DEFAULT ; 
 int SWS_CS_ITU601 ; 
 int SWS_CS_ITU709 ; 
 int SWS_CS_SMPTE240M ; 

int hb_sws_get_colorspace(int color_matrix)
{
    int color_space = SWS_CS_DEFAULT;

    switch (color_matrix)
    {
        case HB_COLR_MAT_SMPTE170M:
            color_space = SWS_CS_ITU601;
            break;
        case HB_COLR_MAT_SMPTE240M:
            color_space = SWS_CS_SMPTE240M;
            break;
        case HB_COLR_MAT_BT709:
            color_space = SWS_CS_ITU709;
            break;
        case HB_COLR_MAT_BT2020_CL:
        case HB_COLR_MAT_BT2020_NCL:
            color_space = SWS_CS_BT2020;
            break;
        default:
            break;
    }

    return color_space;
}