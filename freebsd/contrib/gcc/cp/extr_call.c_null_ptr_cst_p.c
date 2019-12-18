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

/* Variables and functions */
 scalar_t__ CP_INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ integer_zerop (scalar_t__) ; 
 scalar_t__ integral_constant_value (scalar_t__) ; 
 scalar_t__ null_node ; 

bool
null_ptr_cst_p (tree t)
{
  /* [conv.ptr]

     A null pointer constant is an integral constant expression
     (_expr.const_) rvalue of integer type that evaluates to zero.  */
  t = integral_constant_value (t);
  if (t == null_node)
    return true;
  if (CP_INTEGRAL_TYPE_P (TREE_TYPE (t)) && integer_zerop (t))
    {
      STRIP_NOPS (t);
      if (!TREE_CONSTANT_OVERFLOW (t))
	return true;
    }
  return false;
}