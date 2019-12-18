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
typedef  TYPE_1__* constraint_graph_t ;
struct TYPE_3__ {scalar_t__* succs; } ;

/* Variables and functions */
 scalar_t__ bitmap_bit_p (scalar_t__,unsigned int) ; 

__attribute__((used)) static bool
valid_graph_edge (constraint_graph_t graph, unsigned int src,
		  unsigned int dest)
{
  return (graph->succs[dest]
	  && bitmap_bit_p (graph->succs[dest], src));
}