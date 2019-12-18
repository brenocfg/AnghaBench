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
 scalar_t__ CONVERT_EXPR ; 
 scalar_t__ NON_LVALUE_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_CONSTANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
really_constant_p (tree exp)
{
  /* This is not quite the same as STRIP_NOPS.  It does more.  */
  while (TREE_CODE (exp) == NOP_EXPR
	 || TREE_CODE (exp) == CONVERT_EXPR
	 || TREE_CODE (exp) == NON_LVALUE_EXPR)
    exp = TREE_OPERAND (exp, 0);
  return TREE_CONSTANT (exp);
}