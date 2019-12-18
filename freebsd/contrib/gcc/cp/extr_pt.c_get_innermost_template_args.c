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
 int /*<<< orphan*/  SET_TMPL_ARGS_LEVEL (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int TMPL_ARGS_DEPTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMPL_ARGS_LEVEL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  make_tree_vec (int) ; 

tree
get_innermost_template_args (tree args, int n)
{
  tree new_args;
  int extra_levels;
  int i;

  gcc_assert (n >= 0);

  /* If N is 1, just return the innermost set of template arguments.  */
  if (n == 1)
    return TMPL_ARGS_LEVEL (args, TMPL_ARGS_DEPTH (args));

  /* If we're not removing anything, just return the arguments we were
     given.  */
  extra_levels = TMPL_ARGS_DEPTH (args) - n;
  gcc_assert (extra_levels >= 0);
  if (extra_levels == 0)
    return args;

  /* Make a new set of arguments, not containing the outer arguments.  */
  new_args = make_tree_vec (n);
  for (i = 1; i <= n; ++i)
    SET_TMPL_ARGS_LEVEL (new_args, i,
			 TMPL_ARGS_LEVEL (args, i + extra_levels));

  return new_args;
}