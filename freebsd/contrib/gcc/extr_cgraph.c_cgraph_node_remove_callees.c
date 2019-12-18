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
struct cgraph_node {int /*<<< orphan*/ * call_site_hash; struct cgraph_edge* callees; } ;
struct cgraph_edge {struct cgraph_edge* next_callee; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgraph_edge_remove_callee (struct cgraph_edge*) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ *) ; 

void
cgraph_node_remove_callees (struct cgraph_node *node)
{
  struct cgraph_edge *e;

  /* It is sufficient to remove the edges from the lists of callers of
     the callees.  The callee list of the node can be zapped with one
     assignment.  */
  for (e = node->callees; e; e = e->next_callee)
    cgraph_edge_remove_callee (e);
  node->callees = NULL;
  if (node->call_site_hash)
    {
      htab_delete (node->call_site_hash);
      node->call_site_hash = NULL;
    }
}