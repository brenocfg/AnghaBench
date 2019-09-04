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
struct TYPE_7__ {int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_6__ {TYPE_3__* src; } ;
struct TYPE_5__ {int /*<<< orphan*/  phase; int /*<<< orphan*/  magnitude; } ;
typedef  TYPE_1__ SpectrumSynthContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int ff_request_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    SpectrumSynthContext *s = ctx->priv;
    int ret;

    if (!s->magnitude) {
        ret = ff_request_frame(ctx->inputs[0]);
        if (ret < 0)
            return ret;
    }
    if (!s->phase) {
        ret = ff_request_frame(ctx->inputs[1]);
        if (ret < 0)
            return ret;
    }
    return 0;
}