#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  graph; } ;
struct TYPE_5__ {TYPE_1__ video_filters; } ;
typedef  TYPE_2__ hb_work_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_avfilter_graph_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_video_filters(hb_work_private_t *pv)
{
    hb_avfilter_graph_close(&pv->video_filters.graph);
}