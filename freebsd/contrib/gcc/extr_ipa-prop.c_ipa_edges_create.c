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
struct ipa_edge {int dummy; } ;
struct cgraph_node {struct cgraph_edge* callees; struct cgraph_node* next; } ;
struct cgraph_edge {int /*<<< orphan*/  aux; struct cgraph_edge* next_callee; } ;

/* Variables and functions */
 struct cgraph_node* cgraph_nodes ; 
 int /*<<< orphan*/  xcalloc (int,int) ; 

void
ipa_edges_create (void)
{
  struct cgraph_node *node;
  struct cgraph_edge *cs;

  for (node = cgraph_nodes; node; node = node->next)
    for (cs = node->callees; cs; cs = cs->next_callee)
      cs->aux = xcalloc (1, sizeof (struct ipa_edge));
}