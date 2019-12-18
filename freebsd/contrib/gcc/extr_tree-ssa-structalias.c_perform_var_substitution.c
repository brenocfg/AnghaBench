#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct scc_info {unsigned int* node_mapping; int /*<<< orphan*/  visited; } ;
typedef  TYPE_1__* constraint_graph_t ;
struct TYPE_9__ {char* name; } ;
struct TYPE_8__ {int /*<<< orphan*/  nonpointer_vars; } ;
struct TYPE_7__ {unsigned int size; int* label; int /*<<< orphan*/  direct_nodes; } ;

/* Variables and functions */
 unsigned int FIRST_REF_NODE ; 
 unsigned int LAST_REF_NODE ; 
 int TDF_DETAILS ; 
 int TEST_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bitmap_obstack_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_edges_for_node (TYPE_1__*,unsigned int) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 scalar_t__ equivalence_class ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*,...) ; 
 TYPE_5__* get_varinfo (unsigned int) ; 
 struct scc_info* init_scc_info (unsigned int) ; 
 int /*<<< orphan*/  iteration_obstack ; 
 int /*<<< orphan*/  label_visit (TYPE_1__*,struct scc_info*,unsigned int) ; 
 TYPE_2__ stats ; 

__attribute__((used)) static struct scc_info *
perform_var_substitution (constraint_graph_t graph)
{
  unsigned int i;
  unsigned int size = graph->size;
  struct scc_info *si = init_scc_info (size);

  bitmap_obstack_initialize (&iteration_obstack);
  equivalence_class = 0;

  /* We only need to visit the non-address nodes for labeling
     purposes, as the address nodes will never have any predecessors,
     because &x never appears on the LHS of a constraint.  */
  for (i = 0; i < LAST_REF_NODE; i++)
    if (!TEST_BIT (si->visited, si->node_mapping[i]))
      label_visit (graph, si, si->node_mapping[i]);

  if (dump_file && (dump_flags & TDF_DETAILS))
    for (i = 0; i < FIRST_REF_NODE; i++)
      {
	bool direct_node = TEST_BIT (graph->direct_nodes, i);
	fprintf (dump_file,
		 "Equivalence class for %s node id %d:%s is %d\n",
		 direct_node ? "Direct node" : "Indirect node", i,
		 get_varinfo (i)->name,
		 graph->label[si->node_mapping[i]]);
      }

  /* Quickly eliminate our non-pointer variables.  */

  for (i = 0; i < FIRST_REF_NODE; i++)
    {
      unsigned int node = si->node_mapping[i];

      if (graph->label[node] == 0 && TEST_BIT (graph->direct_nodes, node))
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file,
		     "%s is a non-pointer variable, eliminating edges.\n",
		     get_varinfo (node)->name);
	  stats.nonpointer_vars++;
	  clear_edges_for_node (graph, node);
	}
    }
  return si;
}