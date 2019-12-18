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
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ BINFO_VTABLE (scalar_t__) ; 
 scalar_t__ PLUS_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree
get_vtbl_decl_for_binfo (tree binfo)
{
  tree decl;

  decl = BINFO_VTABLE (binfo);
  if (decl && TREE_CODE (decl) == PLUS_EXPR)
    {
      gcc_assert (TREE_CODE (TREE_OPERAND (decl, 0)) == ADDR_EXPR);
      decl = TREE_OPERAND (TREE_OPERAND (decl, 0), 0);
    }
  if (decl)
    gcc_assert (TREE_CODE (decl) == VAR_DECL);
  return decl;
}