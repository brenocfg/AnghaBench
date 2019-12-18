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
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_VEC ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ comp_template_args (scalar_t__,scalar_t__) ; 
 int cp_tree_equal (scalar_t__,scalar_t__) ; 
 scalar_t__ same_type_p (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
template_args_equal (tree ot, tree nt)
{
  if (nt == ot)
    return 1;

  if (TREE_CODE (nt) == TREE_VEC)
    /* For member templates */
    return TREE_CODE (ot) == TREE_VEC && comp_template_args (ot, nt);
  else if (TYPE_P (nt))
    return TYPE_P (ot) && same_type_p (ot, nt);
  else if (TREE_CODE (ot) == TREE_VEC || TYPE_P (ot))
    return 0;
  else
    return cp_tree_equal (ot, nt);
}