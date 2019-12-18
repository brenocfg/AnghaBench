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
 scalar_t__ TB_history_stack ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 

__attribute__((used)) static tree
TB_history_prev (void)
{
  if (TB_history_stack)
    {
      TB_history_stack = TREE_CHAIN (TB_history_stack);
      if (TB_history_stack)
	return TREE_VALUE (TB_history_stack);
    }
  return NULL_TREE;
}