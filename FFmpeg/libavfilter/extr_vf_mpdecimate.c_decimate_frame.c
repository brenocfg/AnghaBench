#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__* linesize; scalar_t__* data; } ;
struct TYPE_8__ {scalar_t__ max_drop_count; int drop_count; int vsub; int hsub; } ;
typedef  TYPE_1__ DecimateContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ diff_planes (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emms_c () ; 

__attribute__((used)) static int decimate_frame(AVFilterContext *ctx,
                          AVFrame *cur, AVFrame *ref)
{
    DecimateContext *decimate = ctx->priv;
    int plane;

    if (decimate->max_drop_count > 0 &&
        decimate->drop_count >= decimate->max_drop_count)
        return 0;
    if (decimate->max_drop_count < 0 &&
        (decimate->drop_count-1) > decimate->max_drop_count)
        return 0;

    for (plane = 0; ref->data[plane] && ref->linesize[plane]; plane++) {
        /* use 8x8 SAD even on subsampled planes.  The blocks won't match up with
         * luma blocks, but hopefully nobody is depending on this to catch
         * localized chroma changes that wouldn't exceed the thresholds when
         * diluted by using what's effectively a larger block size.
         */
        int vsub = plane == 1 || plane == 2 ? decimate->vsub : 0;
        int hsub = plane == 1 || plane == 2 ? decimate->hsub : 0;
        if (diff_planes(ctx,
                        cur->data[plane], cur->linesize[plane],
                        ref->data[plane], ref->linesize[plane],
                        AV_CEIL_RSHIFT(ref->width,  hsub),
                        AV_CEIL_RSHIFT(ref->height, vsub))) {
            emms_c();
            return 0;
        }
    }

    emms_c();
    return 1;
}