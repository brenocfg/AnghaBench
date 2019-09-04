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
typedef  enum AVColorPrimaries { ____Placeholder_AVColorPrimaries } AVColorPrimaries ;
struct TYPE_6__ {int /*<<< orphan*/ * kCVImageBufferColorPrimaries_ITU_R_2020; } ;
struct TYPE_5__ {int color_primaries; } ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
#define  AVCOL_PRI_BT2020 130 
#define  AVCOL_PRI_BT709 129 
#define  AVCOL_PRI_UNSPECIFIED 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_color_primaries_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ compat_keys ; 
 int /*<<< orphan*/ * kCVImageBufferColorPrimaries_ITU_R_709_2 ; 

__attribute__((used)) static int get_cv_color_primaries(AVCodecContext *avctx,
                                  CFStringRef *primaries)
{
    enum AVColorPrimaries pri = avctx->color_primaries;
    switch (pri) {
        case AVCOL_PRI_UNSPECIFIED:
            *primaries = NULL;
            break;

        case AVCOL_PRI_BT709:
            *primaries = kCVImageBufferColorPrimaries_ITU_R_709_2;
            break;

        case AVCOL_PRI_BT2020:
            *primaries = compat_keys.kCVImageBufferColorPrimaries_ITU_R_2020;
            break;

        default:
            av_log(avctx, AV_LOG_ERROR, "Color primaries %s is not supported.\n", av_color_primaries_name(pri));
            *primaries = NULL;
            return -1;
    }

    return 0;
}