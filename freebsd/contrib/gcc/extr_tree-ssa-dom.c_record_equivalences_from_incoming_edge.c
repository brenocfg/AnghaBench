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
typedef  scalar_t__ tree ;
struct edge_info {unsigned int max_cond_equivalences; scalar_t__* cond_equivalences; scalar_t__ rhs; scalar_t__ lhs; } ;
typedef  TYPE_1__* edge ;
typedef  scalar_t__ basic_block ;
struct TYPE_3__ {scalar_t__ src; scalar_t__ aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 scalar_t__ get_immediate_dominator (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  record_cond (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  record_equality (scalar_t__,scalar_t__) ; 
 TYPE_1__* single_incoming_edge_ignoring_loop_edges (scalar_t__) ; 

__attribute__((used)) static void
record_equivalences_from_incoming_edge (basic_block bb)
{
  edge e;
  basic_block parent;
  struct edge_info *edge_info;

  /* If our parent block ended with a control statement, then we may be
     able to record some equivalences based on which outgoing edge from
     the parent was followed.  */
  parent = get_immediate_dominator (CDI_DOMINATORS, bb);

  e = single_incoming_edge_ignoring_loop_edges (bb);

  /* If we had a single incoming edge from our parent block, then enter
     any data associated with the edge into our tables.  */
  if (e && e->src == parent)
    {
      unsigned int i;

      edge_info = (struct edge_info *) e->aux;

      if (edge_info)
	{
	  tree lhs = edge_info->lhs;
	  tree rhs = edge_info->rhs;
	  tree *cond_equivalences = edge_info->cond_equivalences;

	  if (lhs)
	    record_equality (lhs, rhs);

	  if (cond_equivalences)
	    {
	      for (i = 0; i < edge_info->max_cond_equivalences; i += 2)
		{
		  tree expr = cond_equivalences[i];
		  tree value = cond_equivalences[i + 1];

		  record_cond (expr, value);
		}
	    }
	}
    }
}