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
 scalar_t__ BLOCK_CHAIN (scalar_t__) ; 
 scalar_t__ BLOCK_SUBBLOCKS (scalar_t__) ; 
 scalar_t__ BLOCK_VARS (scalar_t__) ; 
 scalar_t__ DECL_PRESERVE_P (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_STATIC (scalar_t__) ; 
 scalar_t__ TREE_USED (scalar_t__) ; 
 int /*<<< orphan*/  add_stack_var_conflict (size_t,size_t) ; 
 int /*<<< orphan*/  expand_one_var (scalar_t__,int) ; 
 int /*<<< orphan*/  flag_unit_at_a_time ; 
 int /*<<< orphan*/  resize_stack_vars_conflict (size_t) ; 
 size_t stack_vars_num ; 

__attribute__((used)) static void
expand_used_vars_for_block (tree block, bool toplevel)
{
  size_t i, j, old_sv_num, this_sv_num, new_sv_num;
  tree t;

  old_sv_num = toplevel ? 0 : stack_vars_num;

  /* Expand all variables at this level.  */
  for (t = BLOCK_VARS (block); t ; t = TREE_CHAIN (t))
    if (TREE_USED (t)
	/* Force local static variables to be output when marked by
	   used attribute.  For unit-at-a-time, cgraph code already takes
	   care of this.  */
	|| (!flag_unit_at_a_time && TREE_STATIC (t)
	    && DECL_PRESERVE_P (t)))
      expand_one_var (t, toplevel);

  this_sv_num = stack_vars_num;

  /* Expand all variables at containing levels.  */
  for (t = BLOCK_SUBBLOCKS (block); t ; t = BLOCK_CHAIN (t))
    expand_used_vars_for_block (t, false);

  /* Since we do not track exact variable lifetimes (which is not even
     possible for variables whose address escapes), we mirror the block
     tree in the interference graph.  Here we cause all variables at this
     level, and all sublevels, to conflict.  Do make certain that a
     variable conflicts with itself.  */
  if (old_sv_num < this_sv_num)
    {
      new_sv_num = stack_vars_num;
      resize_stack_vars_conflict (new_sv_num);

      for (i = old_sv_num; i < new_sv_num; ++i)
	for (j = i < this_sv_num ? i+1 : this_sv_num; j-- > old_sv_num ;)
	  add_stack_var_conflict (i, j);
    }
}