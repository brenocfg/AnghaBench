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
#define  HB_COLR_PRI_BT2020 138 
#define  HB_COLR_PRI_BT470M 137 
#define  HB_COLR_PRI_BT709 136 
#define  HB_COLR_PRI_EBUTECH 135 
#define  HB_COLR_PRI_FILM 134 
#define  HB_COLR_PRI_JEDEC_P22 133 
#define  HB_COLR_PRI_SMPTE240M 132 
#define  HB_COLR_PRI_SMPTE428 131 
#define  HB_COLR_PRI_SMPTE431 130 
#define  HB_COLR_PRI_SMPTE432 129 
#define  HB_COLR_PRI_SMPTEC 128 

const char * hb_get_primaries_name(int primaries)
{
    switch (primaries)
    {
        case HB_COLR_PRI_BT709:
            return "bt709";
        case HB_COLR_PRI_BT470M:
            return "bt470m";
        case HB_COLR_PRI_EBUTECH:
            return "bt470bg";
        case HB_COLR_PRI_SMPTEC:
            return "smpte170m";
        case HB_COLR_PRI_SMPTE240M:
            return "smpte240m";
        case HB_COLR_PRI_SMPTE428:
            return "smpte428";
        case HB_COLR_PRI_FILM:
            return "film";
        case HB_COLR_PRI_SMPTE431:
            return "smpte431";
        case HB_COLR_PRI_SMPTE432:
            return "smpte432";
        case HB_COLR_PRI_BT2020:
            return "bt2020";
        case HB_COLR_PRI_JEDEC_P22:
            return "jedec-p22";
        default:
            return NULL;
    }
}