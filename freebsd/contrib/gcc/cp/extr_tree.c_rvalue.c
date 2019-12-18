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
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  NON_LVALUE_EXPR ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build_nop (scalar_t__,scalar_t__) ; 
 scalar_t__ cp_type_quals (scalar_t__) ; 
 scalar_t__ error_operand_p (scalar_t__) ; 
 int /*<<< orphan*/  processing_template_decl ; 
 scalar_t__ real_lvalue_p (scalar_t__) ; 

tree
rvalue (tree expr)
{
  tree type;

  if (error_operand_p (expr))
    return expr;

  /* [basic.lval]

     Non-class rvalues always have cv-unqualified types.  */
  type = TREE_TYPE (expr);
  if (!CLASS_TYPE_P (type) && cp_type_quals (type))
    type = TYPE_MAIN_VARIANT (type);

  if (!processing_template_decl && real_lvalue_p (expr))
    expr = build1 (NON_LVALUE_EXPR, type, expr);
  else if (type != TREE_TYPE (expr))
    expr = build_nop (type, expr);

  return expr;
}