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
struct TYPE_6__ {int format; TYPE_3__* dst; } ;
struct TYPE_5__ {int /*<<< orphan*/  filter; } ;
typedef  TYPE_1__ AudioContrastContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
#define  AV_SAMPLE_FMT_DBL 131 
#define  AV_SAMPLE_FMT_DBLP 130 
#define  AV_SAMPLE_FMT_FLT 129 
#define  AV_SAMPLE_FMT_FLTP 128 
 int /*<<< orphan*/  filter_dbl ; 
 int /*<<< orphan*/  filter_dblp ; 
 int /*<<< orphan*/  filter_flt ; 
 int /*<<< orphan*/  filter_fltp ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    AudioContrastContext *s    = ctx->priv;

    switch (inlink->format) {
    case AV_SAMPLE_FMT_FLT:  s->filter = filter_flt;  break;
    case AV_SAMPLE_FMT_DBL:  s->filter = filter_dbl;  break;
    case AV_SAMPLE_FMT_FLTP: s->filter = filter_fltp; break;
    case AV_SAMPLE_FMT_DBLP: s->filter = filter_dblp; break;
    }

    return 0;
}