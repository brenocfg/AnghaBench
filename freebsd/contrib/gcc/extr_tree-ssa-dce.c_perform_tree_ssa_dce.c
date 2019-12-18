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
struct edge_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  CDI_POST_DOMINATORS ; 
 int /*<<< orphan*/  TV_CONTROL_DEPENDENCES ; 
 int /*<<< orphan*/  calculate_dominance_info (int /*<<< orphan*/ ) ; 
 scalar_t__ cfg_altered ; 
 struct edge_list* create_edge_list () ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  eliminate_unnecessary_stmts () ; 
 int /*<<< orphan*/  find_all_control_dependences (struct edge_list*) ; 
 int /*<<< orphan*/  find_obviously_necessary_stmts (struct edge_list*) ; 
 int /*<<< orphan*/  free_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_edge_list (struct edge_list*) ; 
 int /*<<< orphan*/  last_basic_block ; 
 int /*<<< orphan*/  mark_dfs_back_edges () ; 
 int /*<<< orphan*/  mark_really_necessary_kill_operand_phis () ; 
 int /*<<< orphan*/  print_stats () ; 
 int /*<<< orphan*/  propagate_necessity (struct edge_list*) ; 
 int /*<<< orphan*/  sbitmap_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_dce_done (int) ; 
 int /*<<< orphan*/  tree_dce_init (int) ; 
 int /*<<< orphan*/  visited_control_parents ; 

__attribute__((used)) static void
perform_tree_ssa_dce (bool aggressive)
{
  struct edge_list *el = NULL;

  tree_dce_init (aggressive);

  if (aggressive)
    {
      /* Compute control dependence.  */
      timevar_push (TV_CONTROL_DEPENDENCES);
      calculate_dominance_info (CDI_POST_DOMINATORS);
      el = create_edge_list ();
      find_all_control_dependences (el);
      timevar_pop (TV_CONTROL_DEPENDENCES);

      visited_control_parents = sbitmap_alloc (last_basic_block);
      sbitmap_zero (visited_control_parents);

      mark_dfs_back_edges ();
    }

  find_obviously_necessary_stmts (el);

  propagate_necessity (el);

  mark_really_necessary_kill_operand_phis ();
  eliminate_unnecessary_stmts ();

  if (aggressive)
    free_dominance_info (CDI_POST_DOMINATORS);

  /* If we removed paths in the CFG, then we need to update
     dominators as well.  I haven't investigated the possibility
     of incrementally updating dominators.  */
  if (cfg_altered)
    free_dominance_info (CDI_DOMINATORS);

  /* Debugging dumps.  */
  if (dump_file)
    print_stats ();

  tree_dce_done (aggressive);

  free_edge_list (el);
}