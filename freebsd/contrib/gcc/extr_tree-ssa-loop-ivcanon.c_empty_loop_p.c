#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct tree_niter_desc {int dummy; } ;
struct loop {unsigned int num_nodes; } ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_2__* basic_block ;
struct TYPE_12__ {scalar_t__ has_volatile_ops; } ;
struct TYPE_11__ {int flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
#define  ASM_EXPR 131 
 int /*<<< orphan*/  ASM_VOLATILE_P (scalar_t__) ; 
 int BB_IRREDUCIBLE_LOOP ; 
#define  CALL_EXPR 130 
#define  MODIFY_EXPR 129 
 scalar_t__ PHI_ARG_DEF_FROM_EDGE (scalar_t__,TYPE_1__*) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  PHI_RESULT (scalar_t__) ; 
#define  RETURN_EXPR 128 
 int /*<<< orphan*/  SSA_OP_VIRTUAL_DEFS ; 
 int TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (scalar_t__) ; 
 int /*<<< orphan*/  ZERO_SSA_OPERANDS (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (TYPE_2__*) ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr_invariant_in_loop_p (struct loop*,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__**) ; 
 scalar_t__ get_call_expr_in (scalar_t__) ; 
 TYPE_2__** get_loop_body (struct loop*) ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  number_of_iterations_exit (struct loop*,TYPE_1__*,struct tree_niter_desc*,int) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 TYPE_1__* single_dom_exit (struct loop*) ; 
 TYPE_3__* stmt_ann (scalar_t__) ; 

__attribute__((used)) static bool
empty_loop_p (struct loop *loop)
{
  edge exit;
  struct tree_niter_desc niter;
  tree phi, def;
  basic_block *body;
  block_stmt_iterator bsi;
  unsigned i;
  tree stmt;

  /* If the loop has multiple exits, it is too hard for us to handle.
     Similarly, if the exit is not dominating, we cannot determine
     whether the loop is not infinite.  */
  exit = single_dom_exit (loop);
  if (!exit)
    return false;

  /* The loop must be finite.  */
  if (!number_of_iterations_exit (loop, exit, &niter, false))
    return false;

  /* Values of all loop exit phi nodes must be invariants.  */
  for (phi = phi_nodes (exit->dest); phi; phi = PHI_CHAIN (phi))
    {
      if (!is_gimple_reg (PHI_RESULT (phi)))
	continue;

      def = PHI_ARG_DEF_FROM_EDGE (phi, exit);

      if (!expr_invariant_in_loop_p (loop, def))
	return false;
    }

  /* And there should be no memory modifying or from other reasons
     unremovable statements.  */
  body = get_loop_body (loop);
  for (i = 0; i < loop->num_nodes; i++)
    {
      /* Irreducible region might be infinite.  */
      if (body[i]->flags & BB_IRREDUCIBLE_LOOP)
	{
	  free (body);
	  return false;
	}
	
      for (bsi = bsi_start (body[i]); !bsi_end_p (bsi); bsi_next (&bsi))
	{
	  stmt = bsi_stmt (bsi);
	  if (!ZERO_SSA_OPERANDS (stmt, SSA_OP_VIRTUAL_DEFS)
	      || stmt_ann (stmt)->has_volatile_ops)
	    {
	      free (body);
	      return false;
	    }

	  /* Also, asm statements and calls may have side effects and we
	     cannot change the number of times they are executed.  */
	  switch (TREE_CODE (stmt))
	    {
	    case RETURN_EXPR:
	    case MODIFY_EXPR:
	      stmt = get_call_expr_in (stmt);
	      if (!stmt)
		break;

	    case CALL_EXPR:
	      if (TREE_SIDE_EFFECTS (stmt))
		{
		  free (body);
		  return false;
		}
	      break;

	    case ASM_EXPR:
	      /* We cannot remove volatile assembler.  */
	      if (ASM_VOLATILE_P (stmt))
		{
		  free (body);
		  return false;
		}
	      break;

	    default:
	      break;
	    }
	}
      }
  free (body);

  return true;
}