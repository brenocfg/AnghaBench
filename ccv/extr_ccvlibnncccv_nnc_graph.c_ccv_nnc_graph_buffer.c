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
struct TYPE_3__ {int buffer_size; void* buffer; } ;
typedef  TYPE_1__ ccv_nnc_graph_t ;

/* Variables and functions */
 void* ccmalloc (int) ; 
 void* ccrealloc (void*,int) ; 

void* ccv_nnc_graph_buffer(ccv_nnc_graph_t* const graph, int size)
{
	if (graph->buffer_size >= size)
		return graph->buffer;
	graph->buffer_size = size;
	graph->buffer = (graph->buffer) ? ccrealloc(graph->buffer, size) : ccmalloc(size);
	return graph->buffer;
}