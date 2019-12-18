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
struct TYPE_3__ {scalar_t__* preds; } ;

/* Variables and functions */
 scalar_t__ BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_bit_p (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  bitmap_set_bit (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  predbitmap_obstack ; 

__attribute__((used)) static void
add_pred_graph_edge (constraint_graph_t graph, unsigned int to,
		     unsigned int from)
{
  if (!graph->preds[to])
    graph->preds[to] = BITMAP_ALLOC (&predbitmap_obstack);
  if (!bitmap_bit_p (graph->preds[to], from))
    bitmap_set_bit (graph->preds[to], from);
}