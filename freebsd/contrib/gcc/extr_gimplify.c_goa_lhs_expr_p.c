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
 scalar_t__ CONVERT_EXPR ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ NON_LVALUE_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 

__attribute__((used)) static bool
goa_lhs_expr_p (tree expr, tree addr)
{
  /* Also include casts to other type variants.  The C front end is fond
     of adding these for e.g. volatile variables.  This is like 
     STRIP_TYPE_NOPS but includes the main variant lookup.  */
  while ((TREE_CODE (expr) == NOP_EXPR
          || TREE_CODE (expr) == CONVERT_EXPR
          || TREE_CODE (expr) == NON_LVALUE_EXPR)
         && TREE_OPERAND (expr, 0) != error_mark_node
         && (TYPE_MAIN_VARIANT (TREE_TYPE (expr))
             == TYPE_MAIN_VARIANT (TREE_TYPE (TREE_OPERAND (expr, 0)))))
    expr = TREE_OPERAND (expr, 0);

  if (TREE_CODE (expr) == INDIRECT_REF && TREE_OPERAND (expr, 0) == addr)
    return true;
  if (TREE_CODE (addr) == ADDR_EXPR && expr == TREE_OPERAND (addr, 0))
    return true;
  return false;
}