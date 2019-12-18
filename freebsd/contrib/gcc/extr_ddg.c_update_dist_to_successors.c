#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sbitmap ;
typedef  TYPE_2__* ddg_node_ptr ;
typedef  TYPE_3__* ddg_edge_ptr ;
struct TYPE_7__ {scalar_t__ distance; scalar_t__ latency; TYPE_2__* dest; struct TYPE_7__* next_out; } ;
struct TYPE_5__ {scalar_t__ count; } ;
struct TYPE_6__ {int cuid; TYPE_1__ aux; TYPE_3__* out; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TEST_BIT (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
update_dist_to_successors (ddg_node_ptr u_node, sbitmap nodes, sbitmap tmp)
{
  ddg_edge_ptr e;
  int result = 0;

  for (e = u_node->out; e; e = e->next_out)
    {
      ddg_node_ptr v_node = e->dest;
      int v = v_node->cuid;

      if (TEST_BIT (nodes, v)
	  && (e->distance == 0)
	  && (v_node->aux.count < u_node->aux.count + e->latency))
	{
	  v_node->aux.count = u_node->aux.count + e->latency;
	  SET_BIT (tmp, v);
	  result = 1;
	}
    }
  return result;
}