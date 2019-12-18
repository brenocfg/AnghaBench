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
 scalar_t__ COND_EXPR ; 
 scalar_t__ GOTO_EXPR ; 
 scalar_t__ LABEL_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
not_interesting_stmt (tree stmt)
{
  /* Note that COND_EXPR's aren't interesting because if they were exiting the
     loop, we would have already failed the number of exits tests.  */
  if (TREE_CODE (stmt) == LABEL_EXPR
      || TREE_CODE (stmt) == GOTO_EXPR
      || TREE_CODE (stmt) == COND_EXPR)
    return true;
  return false;
}