#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* dst; } ;
struct TYPE_5__ {TYPE_2__** outputs; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 int ff_filter_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_frame_ref(AVFilterLink *link, AVFrame *in)
{
    AVFilterLink *outlink = link->dst->outputs[1];

    return ff_filter_frame(outlink, in);
}