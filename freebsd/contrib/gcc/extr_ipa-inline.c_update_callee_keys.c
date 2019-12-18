#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  estimated_growth; } ;
struct cgraph_node {struct cgraph_edge* callees; TYPE_1__ global; } ;
struct cgraph_edge {struct cgraph_node* callee; scalar_t__ inline_failed; struct cgraph_edge* next_callee; } ;
typedef  int /*<<< orphan*/  fibheap_t ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  update_caller_keys (int /*<<< orphan*/ ,struct cgraph_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_callee_keys (fibheap_t heap, struct cgraph_node *node,
		    bitmap updated_nodes)
{
  struct cgraph_edge *e;
  node->global.estimated_growth = INT_MIN;

  for (e = node->callees; e; e = e->next_callee)
    if (e->inline_failed)
      update_caller_keys (heap, e->callee, updated_nodes);
    else if (!e->inline_failed)
      update_callee_keys (heap, e->callee, updated_nodes);
}