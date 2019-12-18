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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int /*<<< orphan*/  CEIL_DIV_EXPR ; 
 int /*<<< orphan*/  COMPLETE_OR_VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 int ERROR_MARK ; 
 int FUNCTION_TYPE ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int VOID_TYPE ; 
 int /*<<< orphan*/  char_type_node ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  size_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_int (int) ; 
 int /*<<< orphan*/  size_one_node ; 

__attribute__((used)) static tree
c_size_in_bytes (tree type)
{
  enum tree_code code = TREE_CODE (type);

  if (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK)
    return size_one_node;

  if (!COMPLETE_OR_VOID_TYPE_P (type))
    {
      error ("arithmetic on pointer to an incomplete type");
      return size_one_node;
    }

  /* Convert in case a char is more than one unit.  */
  return size_binop (CEIL_DIV_EXPR, TYPE_SIZE_UNIT (type),
		     size_int (TYPE_PRECISION (char_type_node)
			       / BITS_PER_UNIT));
}