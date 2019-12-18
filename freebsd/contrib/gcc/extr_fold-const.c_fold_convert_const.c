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
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INTEGRAL_TYPE_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ REAL_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ build_real_from_int_cst (scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert_const_int_from_int (scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert_const_int_from_real (int,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert_const_real_from_real (scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
fold_convert_const (enum tree_code code, tree type, tree arg1)
{
  if (TREE_TYPE (arg1) == type)
    return arg1;

  if (POINTER_TYPE_P (type) || INTEGRAL_TYPE_P (type))
    {
      if (TREE_CODE (arg1) == INTEGER_CST)
	return fold_convert_const_int_from_int (type, arg1);
      else if (TREE_CODE (arg1) == REAL_CST)
	return fold_convert_const_int_from_real (code, type, arg1);
    }
  else if (TREE_CODE (type) == REAL_TYPE)
    {
      if (TREE_CODE (arg1) == INTEGER_CST)
	return build_real_from_int_cst (type, arg1);
      if (TREE_CODE (arg1) == REAL_CST)
	return fold_convert_const_real_from_real (type, arg1);
    }
  return NULL_TREE;
}