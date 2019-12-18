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
struct cgraph_varpool_node {struct cgraph_varpool_node* next_needed; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct cgraph_varpool_node* cgraph_varpool_nodes ; 
 int /*<<< orphan*/  dump_cgraph_varpool_node (int /*<<< orphan*/ *,struct cgraph_varpool_node*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void
dump_varpool (FILE *f)
{
  struct cgraph_varpool_node *node;

  fprintf (f, "variable pool:\n\n");
  for (node = cgraph_varpool_nodes; node; node = node->next_needed)
    dump_cgraph_varpool_node (f, node);
}