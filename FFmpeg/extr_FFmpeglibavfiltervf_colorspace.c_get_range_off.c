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
typedef  enum AVColorRange { ____Placeholder_AVColorRange } AVColorRange ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int did_warn_range; } ;
typedef  TYPE_1__ ColorSpaceContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
#define  AVCOL_RANGE_JPEG 130 
#define  AVCOL_RANGE_MPEG 129 
#define  AVCOL_RANGE_UNSPECIFIED 128 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_range_off(AVFilterContext *ctx, int *off,
                         int *y_rng, int *uv_rng,
                         enum AVColorRange rng, int depth)
{
    switch (rng) {
    case AVCOL_RANGE_UNSPECIFIED: {
        ColorSpaceContext *s = ctx->priv;

        if (!s->did_warn_range) {
            av_log(ctx, AV_LOG_WARNING, "Input range not set, assuming tv/mpeg\n");
            s->did_warn_range = 1;
        }
    }
        // fall-through
    case AVCOL_RANGE_MPEG:
        *off = 16 << (depth - 8);
        *y_rng = 219 << (depth - 8);
        *uv_rng = 224 << (depth - 8);
        break;
    case AVCOL_RANGE_JPEG:
        *off = 0;
        *y_rng = *uv_rng = (256 << (depth - 8)) - 1;
        break;
    default:
        return AVERROR(EINVAL);
    }

    return 0;
}