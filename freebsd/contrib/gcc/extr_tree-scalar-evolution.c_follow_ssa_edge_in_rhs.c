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
typedef  int /*<<< orphan*/  t_bool ;
struct loop {int /*<<< orphan*/  num; } ;

/* Variables and functions */
#define  ASSERT_EXPR 133 
 int /*<<< orphan*/  ASSERT_EXPR_VAR (int /*<<< orphan*/ ) ; 
#define  INTEGER_CST 132 
#define  MINUS_EXPR 131 
#define  NOP_EXPR 130 
#define  PLUS_EXPR 129 
#define  SSA_NAME 128 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRIP_TYPE_NOPS (int /*<<< orphan*/ ) ; 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_to_evolution (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  follow_ssa_edge (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t_dont_know ; 
 int /*<<< orphan*/  t_false ; 
 int /*<<< orphan*/  t_true ; 

__attribute__((used)) static t_bool
follow_ssa_edge_in_rhs (struct loop *loop, tree at_stmt, tree rhs, 
			tree halting_phi, tree *evolution_of_loop, int limit)
{
  t_bool res = t_false;
  tree rhs0, rhs1;
  tree type_rhs = TREE_TYPE (rhs);
  tree evol;
  
  /* The RHS is one of the following cases:
     - an SSA_NAME, 
     - an INTEGER_CST,
     - a PLUS_EXPR, 
     - a MINUS_EXPR,
     - an ASSERT_EXPR,
     - other cases are not yet handled.  */
  switch (TREE_CODE (rhs))
    {
    case NOP_EXPR:
      /* This assignment is under the form "a_1 = (cast) rhs.  */
      res = follow_ssa_edge_in_rhs (loop, at_stmt, TREE_OPERAND (rhs, 0),
				    halting_phi, evolution_of_loop, limit);
      *evolution_of_loop = chrec_convert (TREE_TYPE (rhs),
					  *evolution_of_loop, at_stmt);
      break;

    case INTEGER_CST:
      /* This assignment is under the form "a_1 = 7".  */
      res = t_false;
      break;
      
    case SSA_NAME:
      /* This assignment is under the form: "a_1 = b_2".  */
      res = follow_ssa_edge 
	(loop, SSA_NAME_DEF_STMT (rhs), halting_phi, evolution_of_loop, limit);
      break;
      
    case PLUS_EXPR:
      /* This case is under the form "rhs0 + rhs1".  */
      rhs0 = TREE_OPERAND (rhs, 0);
      rhs1 = TREE_OPERAND (rhs, 1);
      STRIP_TYPE_NOPS (rhs0);
      STRIP_TYPE_NOPS (rhs1);

      if (TREE_CODE (rhs0) == SSA_NAME)
	{
	  if (TREE_CODE (rhs1) == SSA_NAME)
	    {
	      /* Match an assignment under the form: 
		 "a = b + c".  */
	      evol = *evolution_of_loop;
	      res = follow_ssa_edge 
		(loop, SSA_NAME_DEF_STMT (rhs0), halting_phi, 
		 &evol, limit);
	      
	      if (res == t_true)
		*evolution_of_loop = add_to_evolution 
		  (loop->num, 
		   chrec_convert (type_rhs, evol, at_stmt), 
		   PLUS_EXPR, rhs1, at_stmt);
	      
	      else if (res == t_false)
		{
		  res = follow_ssa_edge 
		    (loop, SSA_NAME_DEF_STMT (rhs1), halting_phi, 
		     evolution_of_loop, limit);
		  
		  if (res == t_true)
		    *evolution_of_loop = add_to_evolution 
		      (loop->num, 
		       chrec_convert (type_rhs, *evolution_of_loop, at_stmt), 
		       PLUS_EXPR, rhs0, at_stmt);

		  else if (res == t_dont_know)
		    *evolution_of_loop = chrec_dont_know;
		}

	      else if (res == t_dont_know)
		*evolution_of_loop = chrec_dont_know;
	    }
	  
	  else
	    {
	      /* Match an assignment under the form: 
		 "a = b + ...".  */
	      res = follow_ssa_edge 
		(loop, SSA_NAME_DEF_STMT (rhs0), halting_phi, 
		 evolution_of_loop, limit);
	      if (res == t_true)
		*evolution_of_loop = add_to_evolution 
		  (loop->num, chrec_convert (type_rhs, *evolution_of_loop,
					     at_stmt),
		   PLUS_EXPR, rhs1, at_stmt);

	      else if (res == t_dont_know)
		*evolution_of_loop = chrec_dont_know;
	    }
	}
      
      else if (TREE_CODE (rhs1) == SSA_NAME)
	{
	  /* Match an assignment under the form: 
	     "a = ... + c".  */
	  res = follow_ssa_edge 
	    (loop, SSA_NAME_DEF_STMT (rhs1), halting_phi, 
	     evolution_of_loop, limit);
	  if (res == t_true)
	    *evolution_of_loop = add_to_evolution 
	      (loop->num, chrec_convert (type_rhs, *evolution_of_loop,
					 at_stmt),
	       PLUS_EXPR, rhs0, at_stmt);

	  else if (res == t_dont_know)
	    *evolution_of_loop = chrec_dont_know;
	}

      else
	/* Otherwise, match an assignment under the form: 
	   "a = ... + ...".  */
	/* And there is nothing to do.  */
	res = t_false;
      
      break;
      
    case MINUS_EXPR:
      /* This case is under the form "opnd0 = rhs0 - rhs1".  */
      rhs0 = TREE_OPERAND (rhs, 0);
      rhs1 = TREE_OPERAND (rhs, 1);
      STRIP_TYPE_NOPS (rhs0);
      STRIP_TYPE_NOPS (rhs1);

      if (TREE_CODE (rhs0) == SSA_NAME)
	{
	  /* Match an assignment under the form: 
	     "a = b - ...".  */
	  res = follow_ssa_edge (loop, SSA_NAME_DEF_STMT (rhs0), halting_phi, 
				 evolution_of_loop, limit);
	  if (res == t_true)
	    *evolution_of_loop = add_to_evolution 
	      (loop->num, chrec_convert (type_rhs, *evolution_of_loop, at_stmt),
	       MINUS_EXPR, rhs1, at_stmt);

	  else if (res == t_dont_know)
	    *evolution_of_loop = chrec_dont_know;
	}
      else
	/* Otherwise, match an assignment under the form: 
	   "a = ... - ...".  */
	/* And there is nothing to do.  */
	res = t_false;
      
      break;
    
    case ASSERT_EXPR:
      {
	/* This assignment is of the form: "a_1 = ASSERT_EXPR <a_2, ...>"
	   It must be handled as a copy assignment of the form a_1 = a_2.  */
	tree op0 = ASSERT_EXPR_VAR (rhs);
	if (TREE_CODE (op0) == SSA_NAME)
	  res = follow_ssa_edge (loop, SSA_NAME_DEF_STMT (op0),
				 halting_phi, evolution_of_loop, limit);
	else
	  res = t_false;
	break;
      }


    default:
      res = t_false;
      break;
    }
  
  return res;
}