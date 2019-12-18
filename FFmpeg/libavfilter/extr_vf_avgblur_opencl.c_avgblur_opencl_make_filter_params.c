#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {TYPE_3__* dst; } ;
struct TYPE_5__ {scalar_t__ radiusV; scalar_t__ radiusH; int* power; } ;
typedef  TYPE_1__ AverageBlurOpenCLContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */

__attribute__((used)) static int avgblur_opencl_make_filter_params(AVFilterLink *inlink)
{
    AVFilterContext    *ctx = inlink->dst;
    AverageBlurOpenCLContext *s = ctx->priv;
    int i;

    if (s->radiusV <= 0) {
        s->radiusV = s->radiusH;
    }

    for (i = 0; i < 4; i++) {
        s->power[i] = 1;
    }
    return 0;
}