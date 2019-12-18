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
struct TYPE_2__ {int redefined_extern_inline; int finalized; struct cgraph_node* inlined_to; } ;
struct cgraph_node {int analyzed; scalar_t__ reachable; struct cgraph_node* next_needed; TYPE_1__ global; struct cgraph_node* next; TYPE_1__ local; TYPE_1__ rtl; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgraph_node_remove_callees (struct cgraph_node*) ; 
 struct cgraph_node* cgraph_nodes ; 
 struct cgraph_node* cgraph_nodes_queue ; 
 int /*<<< orphan*/  cgraph_remove_node (struct cgraph_node*) ; 
 int /*<<< orphan*/  flag_unit_at_a_time ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cgraph_reset_node (struct cgraph_node *node)
{
  /* If node->output is set, then this is a unit-at-a-time compilation
     and we have already begun whole-unit analysis.  This is *not*
     testing for whether we've already emitted the function.  That
     case can be sort-of legitimately seen with real function
     redefinition errors.  I would argue that the front end should
     never present us with such a case, but don't enforce that for now.  */
  gcc_assert (!node->output);

  /* Reset our data structures so we can analyze the function again.  */
  memset (&node->local, 0, sizeof (node->local));
  memset (&node->global, 0, sizeof (node->global));
  memset (&node->rtl, 0, sizeof (node->rtl));
  node->analyzed = false;
  node->local.redefined_extern_inline = true;
  node->local.finalized = false;

  if (!flag_unit_at_a_time)
    {
      struct cgraph_node *n, *next;

      for (n = cgraph_nodes; n; n = next)
	{
	  next = n->next;
	  if (n->global.inlined_to == node)
	    cgraph_remove_node (n);
	}
    }

  cgraph_node_remove_callees (node);

  /* We may need to re-queue the node for assembling in case
     we already proceeded it and ignored as not needed.  */
  if (node->reachable && !flag_unit_at_a_time)
    {
      struct cgraph_node *n;

      for (n = cgraph_nodes_queue; n; n = n->next_needed)
	if (n == node)
	  break;
      if (!n)
	node->reachable = 0;
    }
}