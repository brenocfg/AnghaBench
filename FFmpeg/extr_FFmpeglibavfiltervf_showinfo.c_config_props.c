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
struct TYPE_6__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_5__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_7__ {TYPE_2__ frame_rate; TYPE_1__ time_base; } ;
typedef  TYPE_3__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_props(AVFilterContext *ctx, AVFilterLink *link, int is_out)
{

    av_log(ctx, AV_LOG_INFO, "config %s time_base: %d/%d, frame_rate: %d/%d\n",
           is_out ? "out" : "in",
           link->time_base.num, link->time_base.den,
           link->frame_rate.num, link->frame_rate.den);

    return 0;
}