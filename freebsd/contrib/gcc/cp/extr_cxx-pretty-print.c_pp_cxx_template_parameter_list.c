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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_VEC_ELT (int /*<<< orphan*/ ,int) ; 
 int TREE_VEC_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_separate_with (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_cxx_template_parameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
pp_cxx_template_parameter_list (cxx_pretty_printer *pp, tree t)
{
  const int n = TREE_VEC_LENGTH (t);
  int i;
  for (i = 0; i < n; ++i)
    {
      if (i)
	pp_cxx_separate_with (pp, ',');
      pp_cxx_template_parameter (pp, TREE_VEC_ELT (t, i));
    }
}