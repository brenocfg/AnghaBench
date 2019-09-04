#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int w; int /*<<< orphan*/  h; TYPE_3__* dst; } ;
struct TYPE_6__ {int grp_width; int /*<<< orphan*/  scan_max; } ;
typedef  TYPE_1__ ReadVitcContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_props(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    ReadVitcContext *s = ctx->priv;

    s->grp_width = inlink->w * 5 / 48;
    av_log(ctx, AV_LOG_DEBUG, "w:%d h:%d grp_width:%d scan_max:%d\n",
            inlink->w, inlink->h, s->grp_width, s->scan_max);
    return 0;
}