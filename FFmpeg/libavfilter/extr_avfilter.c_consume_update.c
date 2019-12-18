#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  frame_count_out; TYPE_1__* dst; } ;
struct TYPE_12__ {int /*<<< orphan*/  pts; } ;
struct TYPE_11__ {int is_disabled; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  ff_inlink_evaluate_timeline_at_frame (TYPE_3__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  ff_inlink_process_commands (TYPE_3__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  ff_update_link_current_pts (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void consume_update(AVFilterLink *link, const AVFrame *frame)
{
    ff_update_link_current_pts(link, frame->pts);
    ff_inlink_process_commands(link, frame);
    link->dst->is_disabled = !ff_inlink_evaluate_timeline_at_frame(link, frame);
    link->frame_count_out++;
}