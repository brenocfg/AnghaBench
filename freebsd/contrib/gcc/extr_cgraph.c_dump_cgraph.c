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
struct cgraph_node {struct cgraph_node* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct cgraph_node* cgraph_nodes ; 
 int /*<<< orphan*/  dump_cgraph_node (int /*<<< orphan*/ *,struct cgraph_node*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void
dump_cgraph (FILE *f)
{
  struct cgraph_node *node;

  fprintf (f, "callgraph:\n\n");
  for (node = cgraph_nodes; node; node = node->next)
    dump_cgraph_node (f, node);
}