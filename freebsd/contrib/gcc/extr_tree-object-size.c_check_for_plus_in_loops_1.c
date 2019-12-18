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
struct object_size_info {int* depths; unsigned int* tos; unsigned int* stack; size_t object_size_type; int /*<<< orphan*/  reexamine; } ;

/* Variables and functions */
 int CALL_EXPR ; 
 int INTEGER_CST ; 
#define  MODIFY_EXPR 130 
 int /*<<< orphan*/  PHI_ARG_DEF (int /*<<< orphan*/ ,int) ; 
#define  PHI_NODE 129 
 int PHI_NUM_ARGS (int /*<<< orphan*/ ) ; 
 int PLUS_EXPR ; 
#define  RETURN_EXPR 128 
 int SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 unsigned int SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bitmap_clear_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * computed ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 
 scalar_t__** object_sizes ; 
 int /*<<< orphan*/  pass_through_call (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_for_plus_in_loops_1 (struct object_size_info *osi, tree var,
			   unsigned int depth)
{
  tree stmt = SSA_NAME_DEF_STMT (var);
  unsigned int varno = SSA_NAME_VERSION (var);

  if (osi->depths[varno])
    {
      if (osi->depths[varno] != depth)
	{
	  unsigned int *sp;

	  /* Found a loop involving pointer addition.  */
	  for (sp = osi->tos; sp > osi->stack; )
	    {
	      --sp;
	      bitmap_clear_bit (osi->reexamine, *sp);
	      bitmap_set_bit (computed[osi->object_size_type], *sp);
	      object_sizes[osi->object_size_type][*sp] = 0;
	      if (*sp == varno)
		break;
	    }
	}
      return;
    }
  else if (! bitmap_bit_p (osi->reexamine, varno))
    return;

  osi->depths[varno] = depth;
  *osi->tos++ = varno;

  switch (TREE_CODE (stmt))
    {
    case RETURN_EXPR:
      gcc_assert (TREE_CODE (TREE_OPERAND (stmt, 0)) == MODIFY_EXPR);
      stmt = TREE_OPERAND (stmt, 0);
      /* FALLTHRU  */

    case MODIFY_EXPR:
      {
	tree rhs = TREE_OPERAND (stmt, 1), arg;
	STRIP_NOPS (rhs);

	if (TREE_CODE (rhs) == CALL_EXPR)
	  {
	    arg = pass_through_call (rhs);
	    if (arg)
	      rhs = arg;
	  }

	if (TREE_CODE (rhs) == SSA_NAME)
	  check_for_plus_in_loops_1 (osi, rhs, depth);
	else if (TREE_CODE (rhs) == PLUS_EXPR)
	  {
	    tree op0 = TREE_OPERAND (rhs, 0);
	    tree op1 = TREE_OPERAND (rhs, 1);
	    tree cst, basevar;

	    if (TREE_CODE (op0) == SSA_NAME)
	      {
		basevar = op0;
		cst = op1;
	      }
	    else
	      {
		basevar = op1;
		cst = op0;
		gcc_assert (TREE_CODE (basevar) == SSA_NAME);
	      }
	    gcc_assert (TREE_CODE (cst) == INTEGER_CST);

	    check_for_plus_in_loops_1 (osi, basevar,
				       depth + !integer_zerop (cst));
	  }
	else
	  gcc_unreachable ();
	break;
      }
    case PHI_NODE:
      {
	int i;

	for (i = 0; i < PHI_NUM_ARGS (stmt); i++)
	  {
	    tree rhs = PHI_ARG_DEF (stmt, i);

	    if (TREE_CODE (rhs) == SSA_NAME)
	      check_for_plus_in_loops_1 (osi, rhs, depth);
	  }
	break;
      }
    default:
      gcc_unreachable ();
    }

  osi->depths[varno] = 0;
  osi->tos--;
}