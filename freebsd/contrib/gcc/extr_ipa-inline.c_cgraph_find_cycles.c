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
struct cgraph_node {struct cgraph_node* aux; struct cgraph_edge* callees; } ;
struct cgraph_edge {struct cgraph_node* callee; struct cgraph_edge* next_callee; } ;
typedef  int /*<<< orphan*/  htab_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 char* cgraph_node_name (struct cgraph_node*) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 void** htab_find_slot (int /*<<< orphan*/ ,struct cgraph_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cgraph_find_cycles (struct cgraph_node *node, htab_t cycles)
{
  struct cgraph_edge *e;

  if (node->aux)
    {
      void **slot;
      slot = htab_find_slot (cycles, node, INSERT);
      if (!*slot)
	{
	  if (dump_file)
	    fprintf (dump_file, "Cycle contains %s\n", cgraph_node_name (node));
	  *slot = node;
	}
      return;
    }

  node->aux = node;
  for (e = node->callees; e; e = e->next_callee)
    cgraph_find_cycles (e->callee, cycles); 
  node->aux = 0;
}