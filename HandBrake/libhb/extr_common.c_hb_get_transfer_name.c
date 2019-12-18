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
#define  HB_COLR_TRA_BT2020_10 136 
#define  HB_COLR_TRA_BT2020_12 135 
#define  HB_COLR_TRA_BT709 134 
#define  HB_COLR_TRA_GAMMA22 133 
#define  HB_COLR_TRA_GAMMA28 132 
#define  HB_COLR_TRA_IEC61966_2_1 131 
#define  HB_COLR_TRA_IEC61966_2_4 130 
#define  HB_COLR_TRA_SMPTE170M 129 
#define  HB_COLR_TRA_SMPTE240M 128 

const char * hb_get_transfer_name(int transfer)
{
    switch (transfer)
    {
        case HB_COLR_TRA_BT709:
            return "bt709";
        case HB_COLR_TRA_GAMMA22:
            return "gamma22";
        case HB_COLR_TRA_GAMMA28:
            return "gamma28";
        case HB_COLR_TRA_SMPTE170M:
            return "smpte170m";
        case HB_COLR_TRA_SMPTE240M:
            return "smpte240m";
        case HB_COLR_TRA_IEC61966_2_1:
            return "iec61966-2-1";
        case HB_COLR_TRA_IEC61966_2_4:
            return "iec61966-2-4";
        case HB_COLR_TRA_BT2020_10:
            return "bt2020-10";
        case HB_COLR_TRA_BT2020_12:
            return "bt2020-12";
        default:
            return NULL;
    }
}