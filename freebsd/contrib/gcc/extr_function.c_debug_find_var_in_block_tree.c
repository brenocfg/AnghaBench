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
 scalar_t__ BLOCK_SUBBLOCKS (scalar_t__) ; 
 scalar_t__ BLOCK_VARS (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 

tree
debug_find_var_in_block_tree (tree var, tree block)
{
  tree t;

  for (t = BLOCK_VARS (block); t; t = TREE_CHAIN (t))
    if (t == var)
      return block;

  for (t = BLOCK_SUBBLOCKS (block); t; t = TREE_CHAIN (t))
    {
      tree ret = debug_find_var_in_block_tree (var, t);
      if (ret)
	return ret;
    }

  return NULL_TREE;
}