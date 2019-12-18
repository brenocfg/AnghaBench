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
 size_t BUILT_IN_MEMCPY ; 
 size_t BUILT_IN_MEMSET ; 
 scalar_t__ BUILT_IN_NORMAL ; 
 scalar_t__ DECL_BUILT_IN_CLASS (int /*<<< orphan*/ ) ; 
 size_t DECL_FUNCTION_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * built_in_decls ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  init_block_clear_fn (char const*) ; 
 int /*<<< orphan*/  init_block_move_fn (char const*) ; 
 int /*<<< orphan*/  set_user_assembler_name (int /*<<< orphan*/ ,char const*) ; 

void
set_builtin_user_assembler_name (tree decl, const char *asmspec)
{
  tree builtin;
  gcc_assert (TREE_CODE (decl) == FUNCTION_DECL
	      && DECL_BUILT_IN_CLASS (decl) == BUILT_IN_NORMAL
	      && asmspec != 0);

  builtin = built_in_decls [DECL_FUNCTION_CODE (decl)];
  set_user_assembler_name (builtin, asmspec);
  if (DECL_FUNCTION_CODE (decl) == BUILT_IN_MEMCPY)
    init_block_move_fn (asmspec);
  else if (DECL_FUNCTION_CODE (decl) == BUILT_IN_MEMSET)
    init_block_clear_fn (asmspec);
}