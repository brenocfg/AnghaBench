#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  edge_iterator ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_2__* basic_block ;
struct TYPE_12__ {int /*<<< orphan*/  succs; } ;
struct TYPE_11__ {scalar_t__ probability; int /*<<< orphan*/  flags; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
#define  COND_EXPR 129 
 int /*<<< orphan*/  COND_EXPR_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 int INTEGER_CST ; 
 scalar_t__ REG_BR_PROB_BASE ; 
 int /*<<< orphan*/  SWITCH_COND (int /*<<< orphan*/ ) ; 
#define  SWITCH_EXPR 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_STRICT_OVERFLOW_CONDITIONAL ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_next (int /*<<< orphan*/ *) ; 
 TYPE_1__* ei_safe_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_start (int /*<<< orphan*/ ) ; 
 TYPE_1__* find_taken_edge (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_defer_overflow_warnings () ; 
 int /*<<< orphan*/  fold_undefer_and_ignore_overflow_warnings () ; 
 int /*<<< orphan*/  fold_undefer_overflow_warnings (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  remove_edge (TYPE_1__*) ; 
 TYPE_1__* single_succ_edge (TYPE_2__*) ; 
 int /*<<< orphan*/  single_succ_p (TYPE_2__*) ; 

__attribute__((used)) static bool
cleanup_control_expr_graph (basic_block bb, block_stmt_iterator bsi)
{
  edge taken_edge;
  bool retval = false;
  tree expr = bsi_stmt (bsi), val;

  if (!single_succ_p (bb))
    {
      edge e;
      edge_iterator ei;
      bool warned;

      fold_defer_overflow_warnings ();

      switch (TREE_CODE (expr))
	{
	case COND_EXPR:
	  val = fold (COND_EXPR_COND (expr));
	  break;

	case SWITCH_EXPR:
	  val = fold (SWITCH_COND (expr));
	  if (TREE_CODE (val) != INTEGER_CST)
	    {
	      fold_undefer_and_ignore_overflow_warnings ();
	      return false;
	    }
	  break;

	default:
	  gcc_unreachable ();
	}

      taken_edge = find_taken_edge (bb, val);
      if (!taken_edge)
	{
	  fold_undefer_and_ignore_overflow_warnings ();
	  return false;
	}

      /* Remove all the edges except the one that is always executed.  */
      warned = false;
      for (ei = ei_start (bb->succs); (e = ei_safe_edge (ei)); )
	{
	  if (e != taken_edge)
	    {
	      if (!warned)
		{
		  fold_undefer_overflow_warnings
		    (true, expr, WARN_STRICT_OVERFLOW_CONDITIONAL);
		  warned = true;
		}

	      taken_edge->probability += e->probability;
	      taken_edge->count += e->count;
	      remove_edge (e);
	      retval = true;
	    }
	  else
	    ei_next (&ei);
	}
      if (!warned)
	fold_undefer_and_ignore_overflow_warnings ();
      if (taken_edge->probability > REG_BR_PROB_BASE)
	taken_edge->probability = REG_BR_PROB_BASE;
    }
  else
    taken_edge = single_succ_edge (bb);

  bsi_remove (&bsi, true);
  taken_edge->flags = EDGE_FALLTHRU;

  /* We removed some paths from the cfg.  */
  free_dominance_info (CDI_DOMINATORS);

  return retval;
}