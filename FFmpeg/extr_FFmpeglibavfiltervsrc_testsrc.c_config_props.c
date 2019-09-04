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
struct TYPE_6__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  sar; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_2__ TestSourceContext ;
struct TYPE_7__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_1__* src; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */

__attribute__((used)) static int config_props(AVFilterLink *outlink)
{
    TestSourceContext *test = outlink->src->priv;

    outlink->w = test->w;
    outlink->h = test->h;
    outlink->sample_aspect_ratio = test->sar;
    outlink->frame_rate = test->frame_rate;
    outlink->time_base  = test->time_base;

    return 0;
}