#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  aom_color_range_t ;
struct TYPE_5__ {int color_range; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AOM_CR_FULL_RANGE ; 
 int /*<<< orphan*/  AOM_CR_STUDIO_RANGE ; 
 int /*<<< orphan*/  AV1E_SET_COLOR_RANGE ; 
#define  AVCOL_RANGE_JPEG 130 
#define  AVCOL_RANGE_MPEG 129 
#define  AVCOL_RANGE_UNSPECIFIED 128 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  codecctl_int (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_color_range(AVCodecContext *avctx)
{
    aom_color_range_t aom_cr;
    switch (avctx->color_range) {
    case AVCOL_RANGE_UNSPECIFIED:
    case AVCOL_RANGE_MPEG:       aom_cr = AOM_CR_STUDIO_RANGE; break;
    case AVCOL_RANGE_JPEG:       aom_cr = AOM_CR_FULL_RANGE;   break;
    default:
        av_log(avctx, AV_LOG_WARNING, "Unsupported color range (%d)\n",
               avctx->color_range);
        return;
    }

    codecctl_int(avctx, AV1E_SET_COLOR_RANGE, aom_cr);
}