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
typedef  enum AVColorTransferCharacteristic { ____Placeholder_AVColorTransferCharacteristic } AVColorTransferCharacteristic ;

/* Variables and functions */
#define  AVCOL_TRC_ARIB_STD_B67 142 
#define  AVCOL_TRC_BT2020_10 141 
#define  AVCOL_TRC_BT2020_12 140 
#define  AVCOL_TRC_BT709 139 
#define  AVCOL_TRC_GAMMA22 138 
#define  AVCOL_TRC_GAMMA28 137 
#define  AVCOL_TRC_IEC61966_2_1 136 
#define  AVCOL_TRC_IEC61966_2_4 135 
#define  AVCOL_TRC_LINEAR 134 
#define  AVCOL_TRC_LOG 133 
#define  AVCOL_TRC_LOG_SQRT 132 
#define  AVCOL_TRC_SMPTE170M 131 
#define  AVCOL_TRC_SMPTE2084 130 
#define  AVCOL_TRC_SMPTE240M 129 
#define  AVCOL_TRC_UNSPECIFIED 128 
 int ZIMG_TRANSFER_2020_10 ; 
 int ZIMG_TRANSFER_2020_12 ; 
 int ZIMG_TRANSFER_240M ; 
 int ZIMG_TRANSFER_470_BG ; 
 int ZIMG_TRANSFER_470_M ; 
 int ZIMG_TRANSFER_601 ; 
 int ZIMG_TRANSFER_709 ; 
 int ZIMG_TRANSFER_ARIB_B67 ; 
 int ZIMG_TRANSFER_IEC_61966_2_1 ; 
 int ZIMG_TRANSFER_IEC_61966_2_4 ; 
 int ZIMG_TRANSFER_LINEAR ; 
 int ZIMG_TRANSFER_LOG_100 ; 
 int ZIMG_TRANSFER_LOG_316 ; 
 int ZIMG_TRANSFER_ST2084 ; 
 int ZIMG_TRANSFER_UNSPECIFIED ; 

__attribute__((used)) static int convert_trc(enum AVColorTransferCharacteristic color_trc)
{
    switch (color_trc) {
    case AVCOL_TRC_UNSPECIFIED:
        return ZIMG_TRANSFER_UNSPECIFIED;
    case AVCOL_TRC_BT709:
        return ZIMG_TRANSFER_709;
    case AVCOL_TRC_GAMMA22:
        return ZIMG_TRANSFER_470_M;
    case AVCOL_TRC_GAMMA28:
        return ZIMG_TRANSFER_470_BG;
    case AVCOL_TRC_SMPTE170M:
        return ZIMG_TRANSFER_601;
    case AVCOL_TRC_SMPTE240M:
        return ZIMG_TRANSFER_240M;
    case AVCOL_TRC_LINEAR:
        return ZIMG_TRANSFER_LINEAR;
    case AVCOL_TRC_LOG:
        return ZIMG_TRANSFER_LOG_100;
    case AVCOL_TRC_LOG_SQRT:
        return ZIMG_TRANSFER_LOG_316;
    case AVCOL_TRC_IEC61966_2_4:
        return ZIMG_TRANSFER_IEC_61966_2_4;
    case AVCOL_TRC_BT2020_10:
        return ZIMG_TRANSFER_2020_10;
    case AVCOL_TRC_BT2020_12:
        return ZIMG_TRANSFER_2020_12;
    case AVCOL_TRC_SMPTE2084:
        return ZIMG_TRANSFER_ST2084;
    case AVCOL_TRC_ARIB_STD_B67:
        return ZIMG_TRANSFER_ARIB_B67;
    case AVCOL_TRC_IEC61966_2_1:
        return ZIMG_TRANSFER_IEC_61966_2_1;
    }
    return ZIMG_TRANSFER_UNSPECIFIED;
}