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
typedef  int /*<<< orphan*/  TREE_ASM_WRITTEN ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ BLOCK_SUBBLOCKS (int /*<<< orphan*/ ) ; 

void
clear_block_marks (tree block)
{
  while (block)
    {
      TREE_ASM_WRITTEN (block) = 0;
      clear_block_marks (BLOCK_SUBBLOCKS (block));
      block = BLOCK_CHAIN (block);
    }
}