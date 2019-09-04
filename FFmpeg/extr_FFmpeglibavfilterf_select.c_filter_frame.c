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
struct TYPE_8__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_7__ {TYPE_3__* dst; } ;
struct TYPE_6__ {size_t select_out; scalar_t__ select; } ;
typedef  TYPE_1__ SelectContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select_frame (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    SelectContext *select = ctx->priv;

    select_frame(ctx, frame);
    if (select->select)
        return ff_filter_frame(ctx->outputs[select->select_out], frame);

    av_frame_free(&frame);
    return 0;
}