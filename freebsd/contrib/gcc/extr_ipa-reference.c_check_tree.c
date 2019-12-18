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
typedef  int /*<<< orphan*/  ipa_reference_local_vars_info_t ;

/* Variables and functions */
 scalar_t__ ARRAY_REF ; 
 scalar_t__ EXC_PTR_EXPR ; 
 scalar_t__ FILTER_EXPR ; 
 scalar_t__ IMAGPART_EXPR ; 
 scalar_t__ INDIRECT_REF_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REALPART_EXPR ; 
 scalar_t__ SSA_VAR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ handled_component_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_tree (ipa_reference_local_vars_info_t local, tree t, bool checking_write)
{
  if ((TREE_CODE (t) == EXC_PTR_EXPR) || (TREE_CODE (t) == FILTER_EXPR))
    return;

  while (TREE_CODE (t) == REALPART_EXPR 
	 || TREE_CODE (t) == IMAGPART_EXPR
	 || handled_component_p (t))
    {
      if (TREE_CODE (t) == ARRAY_REF)
	check_operand (local, TREE_OPERAND (t, 1), false);
      t = TREE_OPERAND (t, 0);
    }

  /* The bottom of an indirect reference can only be read, not
     written.  So just recurse and whatever we find, check it against
     the read bitmaps.  */

  /*  if (INDIRECT_REF_P (t) || TREE_CODE (t) == MEM_REF) */
  /* FIXME when we have array_ref's of pointers.  */
  if (INDIRECT_REF_P (t))
    check_tree (local, TREE_OPERAND (t, 0), false);

  if (SSA_VAR_P (t))
    check_operand (local, t, checking_write);
}