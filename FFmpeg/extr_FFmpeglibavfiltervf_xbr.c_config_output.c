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
struct TYPE_5__ {int n; } ;
typedef  TYPE_1__ XBRContext ;
struct TYPE_7__ {TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_6__ {int w; int h; TYPE_3__* src; } ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    XBRContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];

    outlink->w = inlink->w * s->n;
    outlink->h = inlink->h * s->n;
    return 0;
}