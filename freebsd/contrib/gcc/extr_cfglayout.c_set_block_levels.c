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
typedef  int BLOCK_NUMBER ;

/* Variables and functions */
 int BLOCK_CHAIN (int) ; 
 scalar_t__ BLOCK_SUBBLOCKS (int) ; 

__attribute__((used)) static void
set_block_levels (tree block, int level)
{
  while (block)
    {
      BLOCK_NUMBER (block) = level;
      set_block_levels (BLOCK_SUBBLOCKS (block), level + 1);
      block = BLOCK_CHAIN (block);
    }
}