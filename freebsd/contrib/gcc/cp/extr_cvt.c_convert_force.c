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
 scalar_t__ ADDR_EXPR ; 
 int CONV_C_CAST ; 
 int /*<<< orphan*/  LOOKUP_COMPLAIN ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 scalar_t__ METHOD_TYPE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int POINTER_TYPE ; 
 int REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_FN_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_ptrmemfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  convert_to_pointer_force (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_reference (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_if_not_in_template (int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

tree
convert_force (tree type, tree expr, int convtype)
{
  tree e = expr;
  enum tree_code code = TREE_CODE (type);

  if (code == REFERENCE_TYPE)
    return (fold_if_not_in_template
	    (convert_to_reference (type, e, CONV_C_CAST, LOOKUP_COMPLAIN,
				   NULL_TREE)));

  if (code == POINTER_TYPE)
    return fold_if_not_in_template (convert_to_pointer_force (type, e));

  /* From typeck.c convert_for_assignment */
  if (((TREE_CODE (TREE_TYPE (e)) == POINTER_TYPE && TREE_CODE (e) == ADDR_EXPR
	&& TREE_CODE (TREE_TYPE (e)) == POINTER_TYPE
	&& TREE_CODE (TREE_TYPE (TREE_TYPE (e))) == METHOD_TYPE)
       || integer_zerop (e)
       || TYPE_PTRMEMFUNC_P (TREE_TYPE (e)))
      && TYPE_PTRMEMFUNC_P (type))
    /* compatible pointer to member functions.  */
    return build_ptrmemfunc (TYPE_PTRMEMFUNC_FN_TYPE (type), e, 1,
			     /*c_cast_p=*/1);

  return ocp_convert (type, e, CONV_C_CAST|convtype, LOOKUP_NORMAL);
}