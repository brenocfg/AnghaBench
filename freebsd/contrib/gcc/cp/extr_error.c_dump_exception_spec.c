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
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_type (scalar_t__,int) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_cxx_left_paren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_right_paren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_whitespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_separate_with_comma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_exception_spec (tree t, int flags)
{
  if (t)
    {
      pp_cxx_identifier (cxx_pp, "throw");
      pp_cxx_whitespace (cxx_pp);
      pp_cxx_left_paren (cxx_pp);
      if (TREE_VALUE (t) != NULL_TREE)
	while (1)
	  {
	    dump_type (TREE_VALUE (t), flags);
	    t = TREE_CHAIN (t);
	    if (!t)
	      break;
	    pp_separate_with_comma (cxx_pp);
	  }
      pp_cxx_right_paren (cxx_pp);
    }
}