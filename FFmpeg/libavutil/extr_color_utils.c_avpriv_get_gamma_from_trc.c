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
#define  AVCOL_TRC_BT1361_ECG 137 
#define  AVCOL_TRC_BT2020_10 136 
#define  AVCOL_TRC_BT2020_12 135 
#define  AVCOL_TRC_BT709 134 
#define  AVCOL_TRC_GAMMA22 133 
#define  AVCOL_TRC_GAMMA28 132 
#define  AVCOL_TRC_IEC61966_2_1 131 
#define  AVCOL_TRC_LINEAR 130 
#define  AVCOL_TRC_SMPTE170M 129 
#define  AVCOL_TRC_SMPTE240M 128 

double avpriv_get_gamma_from_trc(enum AVColorTransferCharacteristic trc)
{
    double gamma;
    switch (trc) {
        case AVCOL_TRC_BT709:
        case AVCOL_TRC_SMPTE170M:
        case AVCOL_TRC_SMPTE240M:
        case AVCOL_TRC_BT1361_ECG:
        case AVCOL_TRC_BT2020_10:
        case AVCOL_TRC_BT2020_12:
            /* these share a segmented TRC, but gamma 1.961 is a close
              approximation, and also more correct for decoding content */
            gamma = 1.961;
            break;
        case AVCOL_TRC_GAMMA22:
        case AVCOL_TRC_IEC61966_2_1:
            gamma = 2.2;
            break;
        case AVCOL_TRC_GAMMA28:
            gamma = 2.8;
            break;
        case AVCOL_TRC_LINEAR:
            gamma = 1.0;
            break;
        default:
            gamma = 0.0; // Unknown value representation
    }
    return gamma;
}