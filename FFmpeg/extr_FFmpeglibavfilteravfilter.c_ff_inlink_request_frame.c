#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int frame_wanted_out; int /*<<< orphan*/  src; int /*<<< orphan*/  status_out; int /*<<< orphan*/  status_in; } ;
typedef  TYPE_1__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  ff_filter_set_ready (int /*<<< orphan*/ ,int) ; 

void ff_inlink_request_frame(AVFilterLink *link)
{
    av_assert1(!link->status_in);
    av_assert1(!link->status_out);
    link->frame_wanted_out = 1;
    ff_filter_set_ready(link->src, 100);
}