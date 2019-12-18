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
typedef  int /*<<< orphan*/  tree ;
struct loop {scalar_t__ header; } ;
typedef  scalar_t__ basic_block ;

/* Variables and functions */
 scalar_t__ CALL_EXPR ; 
 scalar_t__ MOVE_IMPOSSIBLE ; 
 scalar_t__ SSA_NAME ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bb_with_exit_edge_p (struct loop*,scalar_t__) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 scalar_t__ movement_possibility (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_stmt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_could_trap_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
if_convertible_modify_expr_p (struct loop *loop, basic_block bb, tree m_expr)
{
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "-------------------------\n");
      print_generic_stmt (dump_file, m_expr, TDF_SLIM);
    }

  /* Be conservative and do not handle immovable expressions.  */
  if (movement_possibility (m_expr) == MOVE_IMPOSSIBLE)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "stmt is movable. Don't take risk\n");
      return false;
    }

  /* See if it needs speculative loading or not.  */
  if (bb != loop->header
      && tree_could_trap_p (TREE_OPERAND (m_expr, 1)))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "tree could trap...\n");
      return false;
    }

  if (TREE_CODE (TREE_OPERAND (m_expr, 1)) == CALL_EXPR)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "CALL_EXPR \n");
      return false;
    }

  if (TREE_CODE (TREE_OPERAND (m_expr, 0)) != SSA_NAME
      && bb != loop->header
      && !bb_with_exit_edge_p (loop, bb))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, "LHS is not var\n");
	  print_generic_stmt (dump_file, m_expr, TDF_SLIM);
	}
      return false;
    }


  return true;
}