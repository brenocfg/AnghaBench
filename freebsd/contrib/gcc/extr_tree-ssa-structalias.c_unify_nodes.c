#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* constraint_graph_t ;
struct TYPE_10__ {char* name; int /*<<< orphan*/  oldsolution; int /*<<< orphan*/  solution; } ;
struct TYPE_9__ {scalar_t__ iterations; int /*<<< orphan*/  unified_vars_static; int /*<<< orphan*/  unified_vars_dynamic; } ;
struct TYPE_8__ {scalar_t__* succs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESET_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int TDF_DETAILS ; 
 scalar_t__ TEST_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bitmap_clear_bit (scalar_t__,unsigned int) ; 
 scalar_t__ bitmap_ior_into (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  changed ; 
 scalar_t__ changed_count ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 unsigned int find (unsigned int) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_7__* get_varinfo (unsigned int) ; 
 int /*<<< orphan*/  merge_graph_nodes (TYPE_1__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  merge_node_constraints (TYPE_1__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  oldpta_obstack ; 
 TYPE_4__ stats ; 
 scalar_t__ valid_graph_edge (TYPE_1__*,unsigned int,unsigned int) ; 

__attribute__((used)) static void
unify_nodes (constraint_graph_t graph, unsigned int to, unsigned int from,
	     bool update_changed)
{

  gcc_assert (to != from && find (to) == to);
  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "Unifying %s to %s\n",
	     get_varinfo (from)->name,
	     get_varinfo (to)->name);

  if (update_changed)
    stats.unified_vars_dynamic++;
  else
    stats.unified_vars_static++;

  merge_graph_nodes (graph, to, from);
  merge_node_constraints (graph, to, from);

  if (update_changed && TEST_BIT (changed, from))
    {
      RESET_BIT (changed, from);
      if (!TEST_BIT (changed, to))
	SET_BIT (changed, to);
      else
	{
	  gcc_assert (changed_count > 0);
	  changed_count--;
	}
    }

  /* If the solution changes because of the merging, we need to mark
     the variable as changed.  */
  if (bitmap_ior_into (get_varinfo (to)->solution,
		       get_varinfo (from)->solution))
    {
      if (update_changed && !TEST_BIT (changed, to))
	{
	  SET_BIT (changed, to);
	  changed_count++;
	}
    }

  BITMAP_FREE (get_varinfo (from)->solution);
  BITMAP_FREE (get_varinfo (from)->oldsolution);

  if (stats.iterations > 0)
    {
      BITMAP_FREE (get_varinfo (to)->oldsolution);
      get_varinfo (to)->oldsolution = BITMAP_ALLOC (&oldpta_obstack);
    }

  if (valid_graph_edge (graph, to, to))
    {
      if (graph->succs[to])
	bitmap_clear_bit (graph->succs[to], to);
    }
}