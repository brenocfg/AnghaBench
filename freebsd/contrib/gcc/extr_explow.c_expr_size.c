#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int /*<<< orphan*/  (* expr_size ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  SUBSTITUTE_PLACEHOLDER_IN_EXPR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ WITH_SIZE_EXPR ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  sizetype ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

rtx
expr_size (tree exp)
{
  tree size;

  if (TREE_CODE (exp) == WITH_SIZE_EXPR)
    size = TREE_OPERAND (exp, 1);
  else
    size = SUBSTITUTE_PLACEHOLDER_IN_EXPR (lang_hooks.expr_size (exp), exp);

  return expand_expr (size, NULL_RTX, TYPE_MODE (sizetype), 0);
}