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
struct TYPE_3__ {int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ hb_avfilter_graph_t ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int av_buffersrc_add_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hb_avfilter_add_frame(hb_avfilter_graph_t * graph, AVFrame * frame)
{
    return av_buffersrc_add_frame(graph->input, frame);
}