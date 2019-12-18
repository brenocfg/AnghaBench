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
 int COMPONENT_REF ; 
 scalar_t__ DECL_C_BIT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SIZE (int /*<<< orphan*/ ) ; 
 int ENUMERAL_TYPE ; 
 int /*<<< orphan*/  INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX (scalar_t__,scalar_t__) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_common_type_for_size (int /*<<< orphan*/ ,int) ; 
 scalar_t__ c_promoting_integer_type_p (int /*<<< orphan*/ ) ; 
 scalar_t__ compare_tree_int (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  unsigned_type_node ; 

tree
perform_integral_promotions (tree exp)
{
  tree type = TREE_TYPE (exp);
  enum tree_code code = TREE_CODE (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Normally convert enums to int,
     but convert wide enums to something wider.  */
  if (code == ENUMERAL_TYPE)
    {
      type = c_common_type_for_size (MAX (TYPE_PRECISION (type),
					  TYPE_PRECISION (integer_type_node)),
				     ((TYPE_PRECISION (type)
				       >= TYPE_PRECISION (integer_type_node))
				      && TYPE_UNSIGNED (type)));

      return convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  if (TREE_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (TREE_OPERAND (exp, 1))
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      && 0 > compare_tree_int (DECL_SIZE (TREE_OPERAND (exp, 1)),
			       TYPE_PRECISION (integer_type_node)))
    return convert (integer_type_node, exp);

  if (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      if (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_node))
	return convert (unsigned_type_node, exp);

      return convert (integer_type_node, exp);
    }

  return exp;
}