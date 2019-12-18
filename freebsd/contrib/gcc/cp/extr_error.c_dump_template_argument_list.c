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
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_template_argument (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pp_separate_with_comma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_template_argument_list (tree args, int flags)
{
  int n = TREE_VEC_LENGTH (args);
  int need_comma = 0;
  int i;

  for (i = 0; i< n; ++i)
    {
      if (need_comma)
	pp_separate_with_comma (cxx_pp);
      dump_template_argument (TREE_VEC_ELT (args, i), flags);
      need_comma = 1;
    }
}