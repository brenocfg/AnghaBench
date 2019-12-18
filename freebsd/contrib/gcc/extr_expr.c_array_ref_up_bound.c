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
 scalar_t__ NULL_TREE ; 
 scalar_t__ SUBSTITUTE_PLACEHOLDER_IN_EXPR (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DOMAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 

tree
array_ref_up_bound (tree exp)
{
  tree domain_type = TYPE_DOMAIN (TREE_TYPE (TREE_OPERAND (exp, 0)));

  /* If there is a domain type and it has an upper bound, use it, substituting
     for a PLACEHOLDER_EXPR as needed.  */
  if (domain_type && TYPE_MAX_VALUE (domain_type))
    return SUBSTITUTE_PLACEHOLDER_IN_EXPR (TYPE_MAX_VALUE (domain_type), exp);

  /* Otherwise fail.  */
  return NULL_TREE;
}