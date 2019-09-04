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
typedef  int /*<<< orphan*/ * avpriv_trc_function ;

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
#define  AVCOL_TRC_SMPTE240M 131 
#define  AVCOL_TRC_SMPTEST2084 130 
#define  AVCOL_TRC_SMPTEST428_1 129 
#define  AVCOL_TRC_UNSPECIFIED 128 
 int /*<<< orphan*/ * avpriv_trc_arib_std_b67 ; 
 int /*<<< orphan*/ * avpriv_trc_bt1361 ; 
 int /*<<< orphan*/ * avpriv_trc_bt709 ; 
 int /*<<< orphan*/ * avpriv_trc_gamma22 ; 
 int /*<<< orphan*/ * avpriv_trc_gamma28 ; 
 int /*<<< orphan*/ * avpriv_trc_iec61966_2_1 ; 
 int /*<<< orphan*/ * avpriv_trc_iec61966_2_4 ; 
 int /*<<< orphan*/ * avpriv_trc_linear ; 
 int /*<<< orphan*/ * avpriv_trc_log ; 
 int /*<<< orphan*/ * avpriv_trc_log_sqrt ; 
 int /*<<< orphan*/ * avpriv_trc_smpte240M ; 
 int /*<<< orphan*/ * avpriv_trc_smpte_st2084 ; 
 int /*<<< orphan*/ * avpriv_trc_smpte_st428_1 ; 

avpriv_trc_function avpriv_get_trc_function_from_trc(enum AVColorTransferCharacteristic trc)
{
    avpriv_trc_function func = NULL;
    switch (trc) {
        case AVCOL_TRC_BT709:
        case AVCOL_TRC_SMPTE170M:
        case AVCOL_TRC_BT2020_10:
        case AVCOL_TRC_BT2020_12:
            func = avpriv_trc_bt709;
            break;

        case AVCOL_TRC_GAMMA22:
            func = avpriv_trc_gamma22;
            break;
        case AVCOL_TRC_GAMMA28:
            func = avpriv_trc_gamma28;
            break;

        case AVCOL_TRC_SMPTE240M:
            func = avpriv_trc_smpte240M;
            break;

        case AVCOL_TRC_LINEAR:
            func = avpriv_trc_linear;
            break;

        case AVCOL_TRC_LOG:
            func = avpriv_trc_log;
            break;

        case AVCOL_TRC_LOG_SQRT:
            func = avpriv_trc_log_sqrt;
            break;

        case AVCOL_TRC_IEC61966_2_4:
            func = avpriv_trc_iec61966_2_4;
            break;

        case AVCOL_TRC_BT1361_ECG:
            func = avpriv_trc_bt1361;
            break;

        case AVCOL_TRC_IEC61966_2_1:
            func = avpriv_trc_iec61966_2_1;
            break;

        case AVCOL_TRC_SMPTEST2084:
            func = avpriv_trc_smpte_st2084;
            break;

        case AVCOL_TRC_SMPTEST428_1:
            func = avpriv_trc_smpte_st428_1;
            break;

        case AVCOL_TRC_ARIB_STD_B67:
            func = avpriv_trc_arib_std_b67;
            break;

        case AVCOL_TRC_RESERVED0:
        case AVCOL_TRC_UNSPECIFIED:
        case AVCOL_TRC_RESERVED:
        default:
            break;
    }
    return func;
}