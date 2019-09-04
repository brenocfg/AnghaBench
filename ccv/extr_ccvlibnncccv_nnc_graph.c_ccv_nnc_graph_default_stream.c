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
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;
struct TYPE_3__ {scalar_t__ stream_size; int /*<<< orphan*/ ** streams; } ;
typedef  TYPE_1__ ccv_nnc_graph_t ;

/* Variables and functions */

ccv_nnc_stream_context_t* ccv_nnc_graph_default_stream(const ccv_nnc_graph_t* const graph)
{
	if (graph->streams && graph->stream_size > 0)
		return graph->streams[0];
	return 0;
}