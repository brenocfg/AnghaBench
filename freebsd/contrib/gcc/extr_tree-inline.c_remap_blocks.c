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
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  copy_body_data ;

/* Variables and functions */
 int /*<<< orphan*/ * BLOCK_CHAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BLOCK_SUBBLOCKS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_lexical_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  remap_block (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
remap_blocks (tree block, copy_body_data *id)
{
  tree t;
  tree new = block;

  if (!block)
    return NULL;

  remap_block (&new, id);
  gcc_assert (new != block);
  for (t = BLOCK_SUBBLOCKS (block); t ; t = BLOCK_CHAIN (t))
    add_lexical_block (new, remap_blocks (t, id));
  return new;
}