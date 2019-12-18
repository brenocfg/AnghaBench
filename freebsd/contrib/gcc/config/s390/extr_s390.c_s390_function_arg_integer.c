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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_INT ; 
 scalar_t__ OFFSET_TYPE ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REAL_TYPE ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (int) ; 
 scalar_t__ TARGET_SOFT_FLOAT ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ exact_log2 (int) ; 
 int /*<<< orphan*/  s390_function_arg_float (int,int /*<<< orphan*/ ) ; 
 int s390_function_arg_size (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
s390_function_arg_integer (enum machine_mode mode, tree type)
{
  int size = s390_function_arg_size (mode, type);
  if (size > 8)
    return false;

  /* No type info available for some library calls ...  */
  if (!type)
    return GET_MODE_CLASS (mode) == MODE_INT
	   || (TARGET_SOFT_FLOAT &&  SCALAR_FLOAT_MODE_P (mode));

  /* We accept small integral (and similar) types.  */
  if (INTEGRAL_TYPE_P (type)
      || POINTER_TYPE_P (type)
      || TREE_CODE (type) == OFFSET_TYPE
      || (TARGET_SOFT_FLOAT && TREE_CODE (type) == REAL_TYPE))
    return true;

  /* We also accept structs of size 1, 2, 4, 8 that are not
     passed in floating-point registers.  */
  if (AGGREGATE_TYPE_P (type)
      && exact_log2 (size) >= 0
      && !s390_function_arg_float (mode, type))
    return true;

  return false;
}