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
typedef  char* tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int /*<<< orphan*/  CEIL_DIV_EXPR ; 
 int /*<<< orphan*/  COMPLETE_TYPE_P (char*) ; 
 int ERROR_MARK ; 
 int FUNCTION_BOUNDARY ; 
 int FUNCTION_TYPE ; 
 int TREE_CODE (char*) ; 
 int /*<<< orphan*/  TREE_TYPE (char*) ; 
 int TYPE_ALIGN_UNIT (char*) ; 
 int /*<<< orphan*/  TYPE_IS_SIZETYPE (int /*<<< orphan*/ ) ; 
 int TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (char*) ; 
 int VOID_TYPE ; 
 int /*<<< orphan*/  char_type_node ; 
 int /*<<< orphan*/  error (char*,char const*,char*) ; 
 char* fold_convert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*,...) ; 
 char* size_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* size_int (int) ; 
 char* size_one_node ; 
 int /*<<< orphan*/  size_type_node ; 
 char* size_zero_node ; 
 scalar_t__ warn_pointer_arith ; 

tree
c_sizeof_or_alignof_type (tree type, bool is_sizeof, int complain)
{
  const char *op_name;
  tree value = NULL;
  enum tree_code type_code = TREE_CODE (type);

  op_name = is_sizeof ? "sizeof" : "__alignof__";

  if (type_code == FUNCTION_TYPE)
    {
      if (is_sizeof)
	{
	  if (complain && (pedantic || warn_pointer_arith))
	    pedwarn ("invalid application of %<sizeof%> to a function type");
	  value = size_one_node;
	}
      else
	value = size_int (FUNCTION_BOUNDARY / BITS_PER_UNIT);
    }
  else if (type_code == VOID_TYPE || type_code == ERROR_MARK)
    {
      if (type_code == VOID_TYPE
	  && complain && (pedantic || warn_pointer_arith))
	pedwarn ("invalid application of %qs to a void type", op_name);
      value = size_one_node;
    }
  else if (!COMPLETE_TYPE_P (type))
    {
      if (complain)
	error ("invalid application of %qs to incomplete type %qT ",
	       op_name, type);
      value = size_zero_node;
    }
  else
    {
      if (is_sizeof)
	/* Convert in case a char is more than one unit.  */
	value = size_binop (CEIL_DIV_EXPR, TYPE_SIZE_UNIT (type),
			    size_int (TYPE_PRECISION (char_type_node)
				      / BITS_PER_UNIT));
      else
	value = size_int (TYPE_ALIGN_UNIT (type));
    }

  /* VALUE will have an integer type with TYPE_IS_SIZETYPE set.
     TYPE_IS_SIZETYPE means that certain things (like overflow) will
     never happen.  However, this node should really have type
     `size_t', which is just a typedef for an ordinary integer type.  */
  value = fold_convert (size_type_node, value);
  gcc_assert (!TYPE_IS_SIZETYPE (TREE_TYPE (value)));

  return value;
}