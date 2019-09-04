#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  filter; } ;
struct TYPE_8__ {TYPE_1__* filter; TYPE_4__* priv; } ;
struct TYPE_7__ {int format; TYPE_3__* dst; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;
typedef  TYPE_4__ ADerivativeContext ;

/* Variables and functions */
#define  AV_SAMPLE_FMT_DBLP 131 
#define  AV_SAMPLE_FMT_FLTP 130 
#define  AV_SAMPLE_FMT_S16P 129 
#define  AV_SAMPLE_FMT_S32P 128 
 int /*<<< orphan*/  aderivative_dblp ; 
 int /*<<< orphan*/  aderivative_fltp ; 
 int /*<<< orphan*/  aderivative_s16p ; 
 int /*<<< orphan*/  aderivative_s32p ; 
 int /*<<< orphan*/  aintegral_dblp ; 
 int /*<<< orphan*/  aintegral_fltp ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    ADerivativeContext *s = ctx->priv;

    switch (inlink->format) {
    case AV_SAMPLE_FMT_FLTP: s->filter = aderivative_fltp; break;
    case AV_SAMPLE_FMT_DBLP: s->filter = aderivative_dblp; break;
    case AV_SAMPLE_FMT_S32P: s->filter = aderivative_s32p; break;
    case AV_SAMPLE_FMT_S16P: s->filter = aderivative_s16p; break;
    }

    if (strcmp(ctx->filter->name, "aintegral"))
        return 0;

    switch (inlink->format) {
    case AV_SAMPLE_FMT_FLTP: s->filter = aintegral_fltp; break;
    case AV_SAMPLE_FMT_DBLP: s->filter = aintegral_dblp; break;
    }

    return 0;
}