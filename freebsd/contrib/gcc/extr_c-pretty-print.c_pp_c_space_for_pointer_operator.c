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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_whitespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strip_pointer_operator (int /*<<< orphan*/ ) ; 

void
pp_c_space_for_pointer_operator (c_pretty_printer *pp, tree t)
{
  if (POINTER_TYPE_P (t))
    {
      tree pointee = strip_pointer_operator (TREE_TYPE (t));
      if (TREE_CODE (pointee) != ARRAY_TYPE
	  && TREE_CODE (pointee) != FUNCTION_TYPE)
	pp_c_whitespace (pp);
    }
}