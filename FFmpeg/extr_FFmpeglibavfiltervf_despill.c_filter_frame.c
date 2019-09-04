#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * outputs; TYPE_1__* internal; } ;
struct TYPE_14__ {TYPE_4__* dst; } ;
struct TYPE_13__ {int /*<<< orphan*/  height; } ;
struct TYPE_12__ {int (* execute ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_frame_make_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  do_despill_slice ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_4__*) ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *link, AVFrame *frame)
{
    AVFilterContext *ctx = link->dst;
    int ret;

    if (ret = av_frame_make_writable(frame))
        return ret;

    if (ret = ctx->internal->execute(ctx, do_despill_slice, frame, NULL, FFMIN(frame->height, ff_filter_get_nb_threads(ctx))))
        return ret;

    return ff_filter_frame(ctx->outputs[0], frame);
}