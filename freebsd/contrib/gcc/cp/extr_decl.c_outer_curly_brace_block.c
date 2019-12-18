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
 int /*<<< orphan*/  BLOCK_SUBBLOCKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_NEEDS_BODY_BLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 

__attribute__((used)) static tree
outer_curly_brace_block (tree fndecl)
{
  tree block = BLOCK_SUBBLOCKS (DECL_INITIAL (fndecl));
  if (FUNCTION_NEEDS_BODY_BLOCK (current_function_decl))
    /* Skip the artificial function body block.  */
    block = BLOCK_SUBBLOCKS (block);
  return block;
}