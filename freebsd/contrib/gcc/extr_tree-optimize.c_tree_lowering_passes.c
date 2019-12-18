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
 int /*<<< orphan*/  CDI_POST_DOMINATORS ; 
 int /*<<< orphan*/  DECL_STRUCT_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_lowering_passes ; 
 int /*<<< orphan*/  bitmap_obstack_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_obstack_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compact_blocks () ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  execute_pass_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_cfun () ; 
 int /*<<< orphan*/  push_cfun (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_register_cfg_hooks () ; 

void
tree_lowering_passes (tree fn)
{
  tree saved_current_function_decl = current_function_decl;

  current_function_decl = fn;
  push_cfun (DECL_STRUCT_FUNCTION (fn));
  tree_register_cfg_hooks ();
  bitmap_obstack_initialize (NULL);
  execute_pass_list (all_lowering_passes);
  free_dominance_info (CDI_POST_DOMINATORS);
  compact_blocks ();
  current_function_decl = saved_current_function_decl;
  bitmap_obstack_release (NULL);
  pop_cfun ();
}