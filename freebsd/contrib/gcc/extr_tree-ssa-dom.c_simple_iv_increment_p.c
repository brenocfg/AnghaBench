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
 scalar_t__ MINUS_EXPR ; 
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ PHI_ARG_DEF (scalar_t__,unsigned int) ; 
 scalar_t__ PHI_NODE ; 
 scalar_t__ PHI_NUM_ARGS (scalar_t__) ; 
 scalar_t__ PLUS_EXPR ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ SSA_NAME_DEF_STMT (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 

__attribute__((used)) static bool
simple_iv_increment_p (tree stmt)
{
  tree lhs, rhs, preinc, phi;
  unsigned i;

  if (TREE_CODE (stmt) != MODIFY_EXPR)
    return false;

  lhs = TREE_OPERAND (stmt, 0);
  if (TREE_CODE (lhs) != SSA_NAME)
    return false;

  rhs = TREE_OPERAND (stmt, 1);

  if (TREE_CODE (rhs) != PLUS_EXPR
      && TREE_CODE (rhs) != MINUS_EXPR)
    return false;

  preinc = TREE_OPERAND (rhs, 0);
  if (TREE_CODE (preinc) != SSA_NAME)
    return false;

  phi = SSA_NAME_DEF_STMT (preinc);
  if (TREE_CODE (phi) != PHI_NODE)
    return false;

  for (i = 0; i < (unsigned) PHI_NUM_ARGS (phi); i++)
    if (PHI_ARG_DEF (phi, i) == lhs)
      return true;

  return false;
}