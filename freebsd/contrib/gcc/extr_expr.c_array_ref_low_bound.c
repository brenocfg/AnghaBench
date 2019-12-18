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
 scalar_t__ SUBSTITUTE_PLACEHOLDER_IN_EXPR (scalar_t__,scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DOMAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MIN_VALUE (scalar_t__) ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
array_ref_low_bound (tree exp)
{
  tree domain_type = TYPE_DOMAIN (TREE_TYPE (TREE_OPERAND (exp, 0)));

  /* If a lower bound is specified in EXP, use it.  */
  if (TREE_OPERAND (exp, 2))
    return TREE_OPERAND (exp, 2);

  /* Otherwise, if there is a domain type and it has a lower bound, use it,
     substituting for a PLACEHOLDER_EXPR as needed.  */
  if (domain_type && TYPE_MIN_VALUE (domain_type))
    return SUBSTITUTE_PLACEHOLDER_IN_EXPR (TYPE_MIN_VALUE (domain_type), exp);

  /* Otherwise, return a zero of the appropriate type.  */
  return build_int_cst (TREE_TYPE (TREE_OPERAND (exp, 1)), 0);
}