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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int INTEGER_CST ; 
#define  MODIFY_EXPR 129 
 scalar_t__ PHI_ARG_DEF (scalar_t__,int) ; 
#define  PHI_NODE 128 
 int PHI_NUM_ARGS (scalar_t__) ; 
 scalar_t__ PHI_RESULT (scalar_t__) ; 
 int SSA_NAME ; 
 scalar_t__ SSA_NAME_DEF_STMT (scalar_t__) ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (scalar_t__) ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ c_strlen (scalar_t__,int) ; 
 int simple_cst_equal (scalar_t__,scalar_t__) ; 
 scalar_t__ tree_int_cst_lt (scalar_t__,scalar_t__) ; 
 scalar_t__ tree_int_cst_sgn (scalar_t__) ; 

__attribute__((used)) static bool
get_maxval_strlen (tree arg, tree *length, bitmap visited, int type)
{
  tree var, def_stmt, val;
  
  if (TREE_CODE (arg) != SSA_NAME)
    {
      if (type == 2)
	{
	  val = arg;
	  if (TREE_CODE (val) != INTEGER_CST
	      || tree_int_cst_sgn (val) < 0)
	    return false;
	}
      else
	val = c_strlen (arg, 1);
      if (!val)
	return false;

      if (*length)
	{
	  if (type > 0)
	    {
	      if (TREE_CODE (*length) != INTEGER_CST
		  || TREE_CODE (val) != INTEGER_CST)
		return false;

	      if (tree_int_cst_lt (*length, val))
		*length = val;
	      return true;
	    }
	  else if (simple_cst_equal (val, *length) != 1)
	    return false;
	}

      *length = val;
      return true;
    }

  /* If we were already here, break the infinite cycle.  */
  if (bitmap_bit_p (visited, SSA_NAME_VERSION (arg)))
    return true;
  bitmap_set_bit (visited, SSA_NAME_VERSION (arg));

  var = arg;
  def_stmt = SSA_NAME_DEF_STMT (var);

  switch (TREE_CODE (def_stmt))
    {
      case MODIFY_EXPR:
	{
	  tree rhs;

	  /* The RHS of the statement defining VAR must either have a
	     constant length or come from another SSA_NAME with a constant
	     length.  */
	  rhs = TREE_OPERAND (def_stmt, 1);
	  STRIP_NOPS (rhs);
	  return get_maxval_strlen (rhs, length, visited, type);
	}

      case PHI_NODE:
	{
	  /* All the arguments of the PHI node must have the same constant
	     length.  */
	  int i;

	  for (i = 0; i < PHI_NUM_ARGS (def_stmt); i++)
	    {
	      tree arg = PHI_ARG_DEF (def_stmt, i);

	      /* If this PHI has itself as an argument, we cannot
		 determine the string length of this argument.  However,
		 if we can find a constant string length for the other
		 PHI args then we can still be sure that this is a
		 constant string length.  So be optimistic and just
		 continue with the next argument.  */
	      if (arg == PHI_RESULT (def_stmt))
		continue;

	      if (!get_maxval_strlen (arg, length, visited, type))
		return false;
	    }

	  return true;
	}

      default:
	break;
    }


  return false;
}