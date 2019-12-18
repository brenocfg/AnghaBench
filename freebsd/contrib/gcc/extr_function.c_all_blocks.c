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
typedef  scalar_t__ TREE_ASM_WRITTEN ;

/* Variables and functions */
 scalar_t__ BLOCK_CHAIN (scalar_t__) ; 
 scalar_t__ BLOCK_SUBBLOCKS (scalar_t__) ; 

__attribute__((used)) static int
all_blocks (tree block, tree *vector)
{
  int n_blocks = 0;

  while (block)
    {
      TREE_ASM_WRITTEN (block) = 0;

      /* Record this block.  */
      if (vector)
	vector[n_blocks] = block;

      ++n_blocks;

      /* Record the subblocks, and their subblocks...  */
      n_blocks += all_blocks (BLOCK_SUBBLOCKS (block),
			      vector ? vector + n_blocks : 0);
      block = BLOCK_CHAIN (block);
    }

  return n_blocks;
}