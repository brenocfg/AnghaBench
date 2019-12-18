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
 int /*<<< orphan*/  TREE_VEC_ELT (int /*<<< orphan*/ ,int) ; 
 int TREE_VEC_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  template_args_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
comp_template_args (tree oldargs, tree newargs)
{
  int i;

  if (TREE_VEC_LENGTH (oldargs) != TREE_VEC_LENGTH (newargs))
    return 0;

  for (i = 0; i < TREE_VEC_LENGTH (oldargs); ++i)
    {
      tree nt = TREE_VEC_ELT (newargs, i);
      tree ot = TREE_VEC_ELT (oldargs, i);

      if (! template_args_equal (ot, nt))
	return 0;
    }
  return 1;
}