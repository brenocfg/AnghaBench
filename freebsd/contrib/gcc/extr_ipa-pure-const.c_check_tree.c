#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* funct_state ;
struct TYPE_4__ {scalar_t__ pure_const_state; } ;

/* Variables and functions */
 scalar_t__ ARRAY_REF ; 
 scalar_t__ EXC_PTR_EXPR ; 
 scalar_t__ FILTER_EXPR ; 
 scalar_t__ IMAGPART_EXPR ; 
 scalar_t__ INDIRECT_REF_P (int /*<<< orphan*/ ) ; 
 scalar_t__ IPA_CONST ; 
 void* IPA_NEITHER ; 
 scalar_t__ IPA_PURE ; 
 scalar_t__ REALPART_EXPR ; 
 scalar_t__ SSA_VAR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_operand (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ handled_component_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_tree (funct_state local, tree t, bool checking_write)
{
  if ((TREE_CODE (t) == EXC_PTR_EXPR) || (TREE_CODE (t) == FILTER_EXPR))
    return;

  /* Any tree which is volatile disqualifies thie function from being
     const or pure. */
  if (TREE_THIS_VOLATILE (t))
    {
      local->pure_const_state = IPA_NEITHER;
      return;
    }

  while (TREE_CODE (t) == REALPART_EXPR 
	 || TREE_CODE (t) == IMAGPART_EXPR
	 || handled_component_p (t))
    {
      if (TREE_CODE (t) == ARRAY_REF)
	check_operand (local, TREE_OPERAND (t, 1), false);
      t = TREE_OPERAND (t, 0);
    }

  /* The bottom of an indirect reference can only be read, not
     written.  */
  if (INDIRECT_REF_P (t))
    {
      check_tree (local, TREE_OPERAND (t, 0), false);
      
      /* Any indirect reference that occurs on the lhs
	 disqualifies the function from being pure or const. Any
	 indirect reference that occurs on the rhs disqualifies the
	 function from being const.  */
      if (checking_write) 
	{
	  local->pure_const_state = IPA_NEITHER;
	  return;
	}
      else if (local->pure_const_state == IPA_CONST)
	local->pure_const_state = IPA_PURE;
    }

  if (SSA_VAR_P (t))
    check_operand (local, t, checking_write);
}