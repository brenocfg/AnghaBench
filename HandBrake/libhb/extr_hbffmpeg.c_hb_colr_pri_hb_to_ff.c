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
 int AVCOL_PRI_BT2020 ; 
 int AVCOL_PRI_BT470BG ; 
 int AVCOL_PRI_BT470M ; 
 int AVCOL_PRI_BT709 ; 
 int AVCOL_PRI_JEDEC_P22 ; 
 int AVCOL_PRI_SMPTE170M ; 
 int AVCOL_PRI_SMPTE240M ; 
 int AVCOL_PRI_SMPTE428 ; 
 int AVCOL_PRI_SMPTE431 ; 
 int AVCOL_PRI_SMPTE432 ; 
 int AVCOL_PRI_UNSPECIFIED ; 
#define  HB_COLR_PRI_BT2020 138 
#define  HB_COLR_PRI_BT470M 137 
#define  HB_COLR_PRI_BT709 136 
#define  HB_COLR_PRI_EBUTECH 135 
#define  HB_COLR_PRI_JEDEC_P22 134 
#define  HB_COLR_PRI_SMPTE240M 133 
#define  HB_COLR_PRI_SMPTE428 132 
#define  HB_COLR_PRI_SMPTE431 131 
#define  HB_COLR_PRI_SMPTE432 130 
#define  HB_COLR_PRI_SMPTEC 129 
#define  HB_COLR_PRI_UNDEF 128 

int hb_colr_pri_hb_to_ff(int colr_prim)
{
    switch (colr_prim)
    {
        case HB_COLR_PRI_BT709:
            return AVCOL_PRI_BT709;
        case HB_COLR_PRI_EBUTECH:
            return AVCOL_PRI_BT470BG;
        case HB_COLR_PRI_BT470M:
            return AVCOL_PRI_BT470M;
        case HB_COLR_PRI_SMPTEC:
            return AVCOL_PRI_SMPTE170M;
        case HB_COLR_PRI_SMPTE240M:
            return AVCOL_PRI_SMPTE240M;
        case HB_COLR_PRI_BT2020:
            return AVCOL_PRI_BT2020;
        case HB_COLR_PRI_SMPTE428:
            return AVCOL_PRI_SMPTE428;
        case HB_COLR_PRI_SMPTE431:
            return AVCOL_PRI_SMPTE431;
        case HB_COLR_PRI_SMPTE432:
            return AVCOL_PRI_SMPTE432;
        case HB_COLR_PRI_JEDEC_P22:
            return AVCOL_PRI_JEDEC_P22;
        default:
        case HB_COLR_PRI_UNDEF:
            return AVCOL_PRI_UNSPECIFIED;
    }
}