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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
 scalar_t__ DECL_INITIAL (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_LIST ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  pp_c_initializer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pp_c_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_declarator (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pp_equal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_space (int /*<<< orphan*/ *) ; 

void
pp_c_init_declarator (c_pretty_printer *pp, tree t)
{
  pp_declarator (pp, t);
  /* We don't want to output function definitions here.  There are handled
     elsewhere (and the syntactic form is bogus anyway).  */
  if (TREE_CODE (t) != FUNCTION_DECL && DECL_INITIAL (t))
    {
      tree init = DECL_INITIAL (t);
      /* This C++ bit is handled here because it is easier to do so.
	 In templates, the C++ parser builds a TREE_LIST for a
	 direct-initialization; the TREE_PURPOSE is the variable to
	 initialize and the TREE_VALUE is the initializer.  */
      if (TREE_CODE (init) == TREE_LIST)
	{
	  pp_c_left_paren (pp);
	  pp_expression (pp, TREE_VALUE (init));
	  pp_right_paren (pp);
	}
      else
	{
	  pp_space (pp);
	  pp_equal (pp);
	  pp_space (pp);
	  pp_c_initializer (pp, init);
	}
    }
}