#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVColorTransferCharacteristic { ____Placeholder_AVColorTransferCharacteristic } AVColorTransferCharacteristic ;
struct TYPE_6__ {int /*<<< orphan*/ * kCVImageBufferTransferFunction_ITU_R_2020; } ;
struct TYPE_5__ {int color_trc; } ;
typedef  double Float32 ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  int /*<<< orphan*/ * CFNumberRef ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
#define  AVCOL_TRC_ARIB_STD_B67 137 
#define  AVCOL_TRC_BT2020_10 136 
#define  AVCOL_TRC_BT2020_12 135 
#define  AVCOL_TRC_BT709 134 
#define  AVCOL_TRC_GAMMA22 133 
#define  AVCOL_TRC_GAMMA28 132 
#define  AVCOL_TRC_LINEAR 131 
#define  AVCOL_TRC_SMPTE2084 130 
#define  AVCOL_TRC_SMPTE240M 129 
#define  AVCOL_TRC_UNSPECIFIED 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/ * CFNumberCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  av_color_transfer_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ compat_keys ; 
 int /*<<< orphan*/  kCFNumberFloat32Type ; 
 int /*<<< orphan*/ * kCVImageBufferTransferFunction_ITU_R_2100_HLG ; 
 int /*<<< orphan*/ * kCVImageBufferTransferFunction_ITU_R_709_2 ; 
 int /*<<< orphan*/ * kCVImageBufferTransferFunction_Linear ; 
 int /*<<< orphan*/ * kCVImageBufferTransferFunction_SMPTE_240M_1995 ; 
 int /*<<< orphan*/ * kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ ; 
 int /*<<< orphan*/ * kCVImageBufferTransferFunction_UseGamma ; 

__attribute__((used)) static int get_cv_transfer_function(AVCodecContext *avctx,
                                    CFStringRef *transfer_fnc,
                                    CFNumberRef *gamma_level)
{
    enum AVColorTransferCharacteristic trc = avctx->color_trc;
    Float32 gamma;
    *gamma_level = NULL;

    switch (trc) {
        case AVCOL_TRC_UNSPECIFIED:
            *transfer_fnc = NULL;
            break;

        case AVCOL_TRC_BT709:
            *transfer_fnc = kCVImageBufferTransferFunction_ITU_R_709_2;
            break;

        case AVCOL_TRC_SMPTE240M:
            *transfer_fnc = kCVImageBufferTransferFunction_SMPTE_240M_1995;
            break;

#if HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        case AVCOL_TRC_SMPTE2084:
            *transfer_fnc = kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
            break;
#endif
#if HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_LINEAR
        case AVCOL_TRC_LINEAR:
            *transfer_fnc = kCVImageBufferTransferFunction_Linear;
            break;
#endif
#if HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        case AVCOL_TRC_ARIB_STD_B67:
            *transfer_fnc = kCVImageBufferTransferFunction_ITU_R_2100_HLG;
            break;
#endif

        case AVCOL_TRC_GAMMA22:
            gamma = 2.2;
            *transfer_fnc = kCVImageBufferTransferFunction_UseGamma;
            *gamma_level = CFNumberCreate(NULL, kCFNumberFloat32Type, &gamma);
            break;

        case AVCOL_TRC_GAMMA28:
            gamma = 2.8;
            *transfer_fnc = kCVImageBufferTransferFunction_UseGamma;
            *gamma_level = CFNumberCreate(NULL, kCFNumberFloat32Type, &gamma);
            break;

        case AVCOL_TRC_BT2020_10:
        case AVCOL_TRC_BT2020_12:
            *transfer_fnc = compat_keys.kCVImageBufferTransferFunction_ITU_R_2020;
            break;

        default:
            *transfer_fnc = NULL;
            av_log(avctx, AV_LOG_ERROR, "Transfer function %s is not supported.\n", av_color_transfer_name(trc));
            return -1;
    }

    return 0;
}