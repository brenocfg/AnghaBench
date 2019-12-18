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

/* Variables and functions */
 scalar_t__ METHOD_TYPE ; 
 scalar_t__ PTRMEM_CST ; 
 int /*<<< orphan*/  PTRMEM_CST_MEMBER (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_CLASS_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_addr_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_nop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_member_function_from_ptrfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_dummy_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ warn_pmf2ptr ; 

tree
convert_member_func_to_ptr (tree type, tree expr)
{
  tree intype;
  tree decl;

  intype = TREE_TYPE (expr);
  gcc_assert (TYPE_PTRMEMFUNC_P (intype)
	      || TREE_CODE (intype) == METHOD_TYPE);

  if (pedantic || warn_pmf2ptr)
    pedwarn ("converting from %qT to %qT", intype, type);

  if (TREE_CODE (intype) == METHOD_TYPE)
    expr = build_addr_func (expr);
  else if (TREE_CODE (expr) == PTRMEM_CST)
    expr = build_address (PTRMEM_CST_MEMBER (expr));
  else
    {
      decl = maybe_dummy_object (TYPE_PTRMEM_CLASS_TYPE (intype), 0);
      decl = build_address (decl);
      expr = get_member_function_from_ptrfunc (&decl, expr);
    }

  return build_nop (type, expr);
}