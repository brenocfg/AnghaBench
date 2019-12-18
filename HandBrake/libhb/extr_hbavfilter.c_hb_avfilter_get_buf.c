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
typedef  int /*<<< orphan*/  hb_buffer_t ;
struct TYPE_3__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  out_time_base; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ hb_avfilter_graph_t ;

/* Variables and functions */
 int av_buffersink_get_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_avframe_to_video_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

hb_buffer_t * hb_avfilter_get_buf(hb_avfilter_graph_t * graph)
{
    int           result;

    result = av_buffersink_get_frame(graph->output, graph->frame);
    if (result >= 0)
    {
        hb_buffer_t * buf;
        buf = hb_avframe_to_video_buffer(graph->frame, graph->out_time_base);
        av_frame_unref(graph->frame);
        return buf;
    }

    return NULL;
}