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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 scalar_t__ ARITHMETIC_TYPE_P (scalar_t__) ; 
 int ENUMERAL_TYPE ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_P (scalar_t__) ; 
 scalar_t__ TYPE_PTR_P (scalar_t__) ; 
 int VECTOR_TYPE ; 
 scalar_t__ composite_pointer_type (scalar_t__,scalar_t__,scalar_t__,scalar_t__,char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ type_after_usual_arithmetic_conversions (scalar_t__,scalar_t__) ; 

tree
common_type (tree t1, tree t2)
{
  enum tree_code code1;
  enum tree_code code2;

  /* If one type is nonsense, bail.  */
  if (t1 == error_mark_node || t2 == error_mark_node)
    return error_mark_node;

  code1 = TREE_CODE (t1);
  code2 = TREE_CODE (t2);

  if ((ARITHMETIC_TYPE_P (t1) || code1 == ENUMERAL_TYPE
       || code1 == VECTOR_TYPE)
      && (ARITHMETIC_TYPE_P (t2) || code2 == ENUMERAL_TYPE
	  || code2 == VECTOR_TYPE))
    return type_after_usual_arithmetic_conversions (t1, t2);

  else if ((TYPE_PTR_P (t1) && TYPE_PTR_P (t2))
	   || (TYPE_PTRMEM_P (t1) && TYPE_PTRMEM_P (t2))
	   || (TYPE_PTRMEMFUNC_P (t1) && TYPE_PTRMEMFUNC_P (t2)))
    return composite_pointer_type (t1, t2, error_mark_node, error_mark_node,
				   "conversion");
  else
    gcc_unreachable ();
}