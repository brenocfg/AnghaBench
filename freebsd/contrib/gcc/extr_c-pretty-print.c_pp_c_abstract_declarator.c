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
 scalar_t__ BLOCK_POINTER_TYPE ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_direct_abstract_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_c_abstract_declarator (c_pretty_printer *pp, tree t)
{
  /* APPLE LOCAL begin blocks */
  if (TREE_CODE (t) == POINTER_TYPE ||
      TREE_CODE (t) == BLOCK_POINTER_TYPE)
   /* APPLE LOCAL end blocks */
    {
      if (TREE_CODE (TREE_TYPE (t)) == ARRAY_TYPE
	  || TREE_CODE (TREE_TYPE (t)) == FUNCTION_TYPE)
	pp_c_right_paren (pp);
      t = TREE_TYPE (t);
    }

  pp_direct_abstract_declarator (pp, t);
}