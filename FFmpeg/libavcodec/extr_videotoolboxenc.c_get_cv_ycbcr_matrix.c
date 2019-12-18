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
struct TYPE_6__ {int /*<<< orphan*/ * kCVImageBufferYCbCrMatrix_ITU_R_2020; } ;
struct TYPE_5__ {int colorspace; } ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
#define  AVCOL_SPC_BT2020_NCL 133 
#define  AVCOL_SPC_BT470BG 132 
#define  AVCOL_SPC_BT709 131 
#define  AVCOL_SPC_SMPTE170M 130 
#define  AVCOL_SPC_SMPTE240M 129 
#define  AVCOL_SPC_UNSPECIFIED 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_color_space_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ compat_keys ; 
 int /*<<< orphan*/ * kCVImageBufferYCbCrMatrix_ITU_R_601_4 ; 
 int /*<<< orphan*/ * kCVImageBufferYCbCrMatrix_ITU_R_709_2 ; 
 int /*<<< orphan*/ * kCVImageBufferYCbCrMatrix_SMPTE_240M_1995 ; 

__attribute__((used)) static int get_cv_ycbcr_matrix(AVCodecContext *avctx, CFStringRef *matrix) {
    switch(avctx->colorspace) {
        case AVCOL_SPC_BT709:
            *matrix = kCVImageBufferYCbCrMatrix_ITU_R_709_2;
            break;

        case AVCOL_SPC_UNSPECIFIED:
            *matrix = NULL;
            break;

        case AVCOL_SPC_BT470BG:
        case AVCOL_SPC_SMPTE170M:
            *matrix = kCVImageBufferYCbCrMatrix_ITU_R_601_4;
            break;

        case AVCOL_SPC_SMPTE240M:
            *matrix = kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
            break;

        case AVCOL_SPC_BT2020_NCL:
            *matrix = compat_keys.kCVImageBufferYCbCrMatrix_ITU_R_2020;
            break;

        default:
            av_log(avctx, AV_LOG_ERROR, "Color space %s is not supported.\n", av_color_space_name(avctx->colorspace));
            return -1;
    }

    return 0;
}