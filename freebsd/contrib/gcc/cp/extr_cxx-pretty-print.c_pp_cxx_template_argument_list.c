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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/ * DECL_TEMPLATE_RESULT (int /*<<< orphan*/ *) ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_VEC_ELT (int /*<<< orphan*/ *,int) ; 
 int TREE_VEC_LENGTH (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_separate_with (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_cxx_type_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_cxx_template_argument_list (cxx_pretty_printer *pp, tree t)
{
  int i;
  if (t == NULL)
    return;
  for (i = 0; i < TREE_VEC_LENGTH (t); ++i)
    {
      tree arg = TREE_VEC_ELT (t, i);
      if (i != 0)
	pp_cxx_separate_with (pp, ',');
      if (TYPE_P (arg) || (TREE_CODE (arg) == TEMPLATE_DECL
			   && TYPE_P (DECL_TEMPLATE_RESULT (arg))))
	pp_cxx_type_id (pp, arg);
      else
	pp_cxx_expression (pp, arg);
    }
}