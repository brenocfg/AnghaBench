#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int color_primaries; int matrix_coefficients; } ;
typedef  TYPE_1__ ProresMetadataContext ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
#define  AVCOL_PRI_BT2020 136 
#define  AVCOL_PRI_BT470BG 135 
#define  AVCOL_PRI_BT709 134 
#define  AVCOL_PRI_SMPTE170M 133 
#define  AVCOL_PRI_SMPTE431 132 
#define  AVCOL_PRI_SMPTE432 131 
#define  AVCOL_SPC_BT2020_NCL 130 
#define  AVCOL_SPC_BT709 129 
#define  AVCOL_SPC_SMPTE170M 128 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int prores_metadata_init(AVBSFContext *bsf)
{
    ProresMetadataContext *ctx = bsf->priv_data;
    /*! check options */
    switch (ctx->color_primaries) {
    case -1:
    case 0:
    case AVCOL_PRI_BT709:
    case AVCOL_PRI_BT470BG:
    case AVCOL_PRI_SMPTE170M:
    case AVCOL_PRI_BT2020:
    case AVCOL_PRI_SMPTE431:
    case AVCOL_PRI_SMPTE432:
        break;
    default:
        av_log(bsf, AV_LOG_ERROR, "Color primaries %d is not a valid value\n", ctx->color_primaries);
        return AVERROR(EINVAL);
    }

    switch (ctx->matrix_coefficients) {
    case -1:
    case 0:
    case AVCOL_SPC_BT709:
    case AVCOL_SPC_SMPTE170M:
    case AVCOL_SPC_BT2020_NCL:
        break;
    default:
        av_log(bsf, AV_LOG_ERROR, "Colorspace %d is not a valid value\n", ctx->matrix_coefficients);
        return AVERROR(EINVAL);
    }

    return 0;
}