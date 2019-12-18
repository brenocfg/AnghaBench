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
 scalar_t__ CONSTRUCTOR ; 
 scalar_t__ INDIRECT_REF_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ SSA_VAR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ handled_component_p (int /*<<< orphan*/ ) ; 

tree
get_base_address (tree t)
{
  while (handled_component_p (t))
    t = TREE_OPERAND (t, 0);
  
  if (SSA_VAR_P (t)
      || TREE_CODE (t) == STRING_CST
      || TREE_CODE (t) == CONSTRUCTOR
      || INDIRECT_REF_P (t))
    return t;
  else
    return NULL_TREE;
}