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
#define  AVCOL_PRI_BT2020 141 
#define  AVCOL_PRI_BT470BG 140 
#define  AVCOL_PRI_BT470M 139 
#define  AVCOL_PRI_BT709 138 
#define  AVCOL_PRI_FILM 137 
#define  AVCOL_PRI_JEDEC_P22 136 
#define  AVCOL_PRI_RESERVED 135 
#define  AVCOL_PRI_RESERVED0 134 
#define  AVCOL_PRI_SMPTE170M 133 
#define  AVCOL_PRI_SMPTE240M 132 
#define  AVCOL_PRI_SMPTE428 131 
#define  AVCOL_PRI_SMPTE431 130 
#define  AVCOL_PRI_SMPTE432 129 
#define  AVCOL_PRI_UNSPECIFIED 128 
 int HB_COLR_PRI_BT2020 ; 
 int HB_COLR_PRI_BT470M ; 
 int HB_COLR_PRI_BT709 ; 
 int HB_COLR_PRI_EBUTECH ; 
 int HB_COLR_PRI_FILM ; 
 int HB_COLR_PRI_JEDEC_P22 ; 
 int HB_COLR_PRI_SMPTE240M ; 
 int HB_COLR_PRI_SMPTE428 ; 
 int HB_COLR_PRI_SMPTE431 ; 
 int HB_COLR_PRI_SMPTE432 ; 
 int HB_COLR_PRI_SMPTEC ; 
 int HB_COLR_PRI_UNDEF ; 

int hb_colr_pri_ff_to_hb(int colr_prim)
{
    switch (colr_prim)
    {
        case AVCOL_PRI_BT709:
            return HB_COLR_PRI_BT709;
        case AVCOL_PRI_BT470M:
            return HB_COLR_PRI_BT470M;
        case AVCOL_PRI_BT470BG:
            return HB_COLR_PRI_EBUTECH;
        case AVCOL_PRI_SMPTE170M:
            return HB_COLR_PRI_SMPTEC;
        case AVCOL_PRI_SMPTE240M:
            return HB_COLR_PRI_SMPTE240M;
        case AVCOL_PRI_FILM:
            return HB_COLR_PRI_FILM;
        case AVCOL_PRI_BT2020:
            return HB_COLR_PRI_BT2020;
        case AVCOL_PRI_SMPTE428:
            return HB_COLR_PRI_SMPTE428;
        case AVCOL_PRI_SMPTE431:
            return HB_COLR_PRI_SMPTE431;
        case AVCOL_PRI_SMPTE432:
            return HB_COLR_PRI_SMPTE432;
        case AVCOL_PRI_JEDEC_P22:
            return HB_COLR_PRI_JEDEC_P22;
        default:
        case AVCOL_PRI_RESERVED:
        case AVCOL_PRI_RESERVED0:
        case AVCOL_PRI_UNSPECIFIED:
            return HB_COLR_PRI_UNDEF;
    }
}