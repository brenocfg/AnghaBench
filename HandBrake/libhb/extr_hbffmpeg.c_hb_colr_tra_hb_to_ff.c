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
 int AVCOL_TRC_ARIB_STD_B67 ; 
 int AVCOL_TRC_BT1361_ECG ; 
 int AVCOL_TRC_BT2020_10 ; 
 int AVCOL_TRC_BT2020_12 ; 
 int AVCOL_TRC_BT709 ; 
 int AVCOL_TRC_GAMMA22 ; 
 int AVCOL_TRC_GAMMA28 ; 
 int AVCOL_TRC_IEC61966_2_1 ; 
 int AVCOL_TRC_IEC61966_2_4 ; 
 int AVCOL_TRC_LINEAR ; 
 int AVCOL_TRC_LOG ; 
 int AVCOL_TRC_LOG_SQRT ; 
 int AVCOL_TRC_SMPTE170M ; 
 int AVCOL_TRC_SMPTE2084 ; 
 int AVCOL_TRC_SMPTE240M ; 
 int AVCOL_TRC_SMPTE428 ; 
 int AVCOL_TRC_UNSPECIFIED ; 
#define  HB_COLR_TRA_ARIB_STD_B67 144 
#define  HB_COLR_TRA_BT1361_ECG 143 
#define  HB_COLR_TRA_BT2020_10 142 
#define  HB_COLR_TRA_BT2020_12 141 
#define  HB_COLR_TRA_BT709 140 
#define  HB_COLR_TRA_GAMMA22 139 
#define  HB_COLR_TRA_GAMMA28 138 
#define  HB_COLR_TRA_IEC61966_2_1 137 
#define  HB_COLR_TRA_IEC61966_2_4 136 
#define  HB_COLR_TRA_LINEAR 135 
#define  HB_COLR_TRA_LOG 134 
#define  HB_COLR_TRA_LOG_SQRT 133 
#define  HB_COLR_TRA_SMPTE170M 132 
#define  HB_COLR_TRA_SMPTE240M 131 
#define  HB_COLR_TRA_SMPTE428 130 
#define  HB_COLR_TRA_SMPTEST2084 129 
#define  HB_COLR_TRA_UNDEF 128 

int hb_colr_tra_hb_to_ff(int colr_tra)
{
    switch (colr_tra)
    {
        case HB_COLR_TRA_BT709:
            return AVCOL_TRC_BT709;
        case HB_COLR_TRA_GAMMA22:
            return AVCOL_TRC_GAMMA22;
        case HB_COLR_TRA_GAMMA28:
            return AVCOL_TRC_GAMMA28;
        case HB_COLR_TRA_SMPTE170M:
            return AVCOL_TRC_SMPTE170M;
        case HB_COLR_TRA_SMPTE240M:
            return AVCOL_TRC_SMPTE240M;
        case HB_COLR_TRA_LINEAR:
            return AVCOL_TRC_LINEAR;
        case HB_COLR_TRA_LOG:
            return AVCOL_TRC_LOG;
        case HB_COLR_TRA_LOG_SQRT:
            return AVCOL_TRC_LOG_SQRT;
        case HB_COLR_TRA_IEC61966_2_4:
            return AVCOL_TRC_IEC61966_2_4;
        case HB_COLR_TRA_BT1361_ECG:
            return AVCOL_TRC_BT1361_ECG;
        case HB_COLR_TRA_IEC61966_2_1:
            return AVCOL_TRC_IEC61966_2_1;
        case HB_COLR_TRA_BT2020_10:
            return AVCOL_TRC_BT2020_10;
        case HB_COLR_TRA_BT2020_12:
            return AVCOL_TRC_BT2020_12;
        case HB_COLR_TRA_SMPTEST2084:
            return AVCOL_TRC_SMPTE2084;
        case HB_COLR_TRA_SMPTE428:
            return AVCOL_TRC_SMPTE428;
        case HB_COLR_TRA_ARIB_STD_B67:
            return AVCOL_TRC_ARIB_STD_B67;
        default:
        case HB_COLR_TRA_UNDEF:
            return AVCOL_TRC_UNSPECIFIED;
    }
}