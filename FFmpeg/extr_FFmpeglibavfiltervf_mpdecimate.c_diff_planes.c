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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int frac; int (* sad ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ;int hi; int lo; } ;
typedef  TYPE_1__ DecimateContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int,...) ; 
 int stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int diff_planes(AVFilterContext *ctx,
                       uint8_t *cur, int cur_linesize,
                       uint8_t *ref, int ref_linesize,
                       int w, int h)
{
    DecimateContext *decimate = ctx->priv;

    int x, y;
    int d, c = 0;
    int t = (w/16)*(h/16)*decimate->frac;

    /* compute difference for blocks of 8x8 bytes */
    for (y = 0; y < h-7; y += 4) {
        for (x = 8; x < w-7; x += 4) {
            d = decimate->sad(cur + y*cur_linesize + x, cur_linesize,
                              ref + y*ref_linesize + x, ref_linesize);
            if (d > decimate->hi) {
                av_log(ctx, AV_LOG_DEBUG, "%d>=hi ", d);
                return 1;
            }
            if (d > decimate->lo) {
                c++;
                if (c > t) {
                    av_log(ctx, AV_LOG_DEBUG, "lo:%d>=%d ", c, t);
                    return 1;
                }
            }
        }
    }

    av_log(ctx, AV_LOG_DEBUG, "lo:%d<%d ", c, t);
    return 0;
}