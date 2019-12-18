#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int status_out; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; int /*<<< orphan*/  frame_wanted_out; } ;
typedef  TYPE_1__ AVFilterLink ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  ff_filter_set_ready (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_update_link_current_pts (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  filter_unblock (int /*<<< orphan*/ ) ; 

void ff_avfilter_link_set_out_status(AVFilterLink *link, int status, int64_t pts)
{
    av_assert0(!link->frame_wanted_out);
    av_assert0(!link->status_out);
    link->status_out = status;
    if (pts != AV_NOPTS_VALUE)
        ff_update_link_current_pts(link, pts);
    filter_unblock(link->dst);
    ff_filter_set_ready(link->src, 200);
}