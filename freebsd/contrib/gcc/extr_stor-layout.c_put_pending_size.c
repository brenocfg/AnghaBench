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
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ SAVE_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pending_sizes ; 
 int /*<<< orphan*/  skip_simple_arithmetic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
put_pending_size (tree expr)
{
  /* Strip any simple arithmetic from EXPR to see if it has an underlying
     SAVE_EXPR.  */
  expr = skip_simple_arithmetic (expr);

  if (TREE_CODE (expr) == SAVE_EXPR)
    pending_sizes = tree_cons (NULL_TREE, expr, pending_sizes);
}