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
#define  AVCOL_TRC_ARIB_STD_B67 146 
#define  AVCOL_TRC_BT1361_ECG 145 
#define  AVCOL_TRC_BT2020_10 144 
#define  AVCOL_TRC_BT2020_12 143 
#define  AVCOL_TRC_BT709 142 
#define  AVCOL_TRC_GAMMA22 141 
#define  AVCOL_TRC_GAMMA28 140 
#define  AVCOL_TRC_IEC61966_2_1 139 
#define  AVCOL_TRC_IEC61966_2_4 138 
#define  AVCOL_TRC_LINEAR 137 
#define  AVCOL_TRC_LOG 136 
#define  AVCOL_TRC_LOG_SQRT 135 
#define  AVCOL_TRC_RESERVED 134 
#define  AVCOL_TRC_RESERVED0 133 
#define  AVCOL_TRC_SMPTE170M 132 
#define  AVCOL_TRC_SMPTE2084 131 
#define  AVCOL_TRC_SMPTE240M 130 
#define  AVCOL_TRC_SMPTE428 129 
#define  AVCOL_TRC_UNSPECIFIED 128 
 int HB_COLR_TRA_ARIB_STD_B67 ; 
 int HB_COLR_TRA_BT1361_ECG ; 
 int HB_COLR_TRA_BT2020_10 ; 
 int HB_COLR_TRA_BT2020_12 ; 
 int HB_COLR_TRA_BT709 ; 
 int HB_COLR_TRA_GAMMA22 ; 
 int HB_COLR_TRA_GAMMA28 ; 
 int HB_COLR_TRA_IEC61966_2_1 ; 
 int HB_COLR_TRA_IEC61966_2_4 ; 
 int HB_COLR_TRA_LINEAR ; 
 int HB_COLR_TRA_LOG ; 
 int HB_COLR_TRA_LOG_SQRT ; 
 int HB_COLR_TRA_SMPTE170M ; 
 int HB_COLR_TRA_SMPTE240M ; 
 int HB_COLR_TRA_SMPTE428 ; 
 int HB_COLR_TRA_SMPTEST2084 ; 
 int HB_COLR_TRA_UNDEF ; 

int hb_colr_tra_ff_to_hb(int colr_tra)
{
    switch (colr_tra)
    {
        case AVCOL_TRC_BT709:
            return HB_COLR_TRA_BT709;
        case AVCOL_TRC_GAMMA22:
            return HB_COLR_TRA_GAMMA22;
        case AVCOL_TRC_GAMMA28:
            return HB_COLR_TRA_GAMMA28;
        case AVCOL_TRC_SMPTE170M:
            return HB_COLR_TRA_SMPTE170M;
        case AVCOL_TRC_SMPTE240M:
            return HB_COLR_TRA_SMPTE240M;
        case AVCOL_TRC_LINEAR:
            return HB_COLR_TRA_LINEAR;
        case AVCOL_TRC_LOG:
            return HB_COLR_TRA_LOG;
        case AVCOL_TRC_LOG_SQRT:
            return HB_COLR_TRA_LOG_SQRT;
        case AVCOL_TRC_IEC61966_2_4:
            return HB_COLR_TRA_IEC61966_2_4;
        case AVCOL_TRC_BT1361_ECG:
            return HB_COLR_TRA_BT1361_ECG;
        case AVCOL_TRC_IEC61966_2_1:
            return HB_COLR_TRA_IEC61966_2_1;
        case AVCOL_TRC_BT2020_10:
            return HB_COLR_TRA_BT2020_10;
        case AVCOL_TRC_BT2020_12:
            return HB_COLR_TRA_BT2020_12;
        case AVCOL_TRC_SMPTE2084:
            return HB_COLR_TRA_SMPTEST2084;
        case AVCOL_TRC_SMPTE428:
            return HB_COLR_TRA_SMPTE428;
        case AVCOL_TRC_ARIB_STD_B67:
            return HB_COLR_TRA_ARIB_STD_B67;
        default:
        case AVCOL_TRC_UNSPECIFIED:
        case AVCOL_TRC_RESERVED:
        case AVCOL_TRC_RESERVED0:
            return HB_COLR_TRA_UNDEF;
    }
}