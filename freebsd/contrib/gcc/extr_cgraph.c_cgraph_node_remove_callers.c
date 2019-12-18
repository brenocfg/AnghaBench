#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cgraph_node {struct cgraph_edge* callers; } ;
struct cgraph_edge {struct cgraph_edge* next_caller; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgraph_edge_remove_caller (struct cgraph_edge*) ; 

__attribute__((used)) static void
cgraph_node_remove_callers (struct cgraph_node *node)
{
  struct cgraph_edge *e;

  /* It is sufficient to remove the edges from the lists of callees of
     the callers.  The caller list of the node can be zapped with one
     assignment.  */
  for (e = node->callers; e; e = e->next_caller)
    cgraph_edge_remove_caller (e);
  node->callers = NULL;
}