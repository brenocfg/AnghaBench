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
 int TMPL_ARGS_DEPTH (scalar_t__) ; 
 scalar_t__ TMPL_ARGS_LEVEL (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_VEC_ELT (scalar_t__,int) ; 
 int TREE_VEC_LENGTH (scalar_t__) ; 
 scalar_t__ dependent_template_arg_p (int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 

bool
any_dependent_template_arguments_p (tree args)
{
  int i;
  int j;

  if (!args)
    return false;
  if (args == error_mark_node)
    return true;

  for (i = 0; i < TMPL_ARGS_DEPTH (args); ++i)
    {
      tree level = TMPL_ARGS_LEVEL (args, i + 1);
      for (j = 0; j < TREE_VEC_LENGTH (level); ++j)
	if (dependent_template_arg_p (TREE_VEC_ELT (level, j)))
	  return true;
    }

  return false;
}