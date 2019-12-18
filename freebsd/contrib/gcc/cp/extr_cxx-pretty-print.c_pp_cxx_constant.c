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
 int PAREN_STRING_LITERAL_P (int /*<<< orphan*/ ) ; 
#define  STRING_CST 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_right_paren (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_cxx_constant (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
    case STRING_CST:
      {
	const bool in_parens = PAREN_STRING_LITERAL_P (t);
	if (in_parens)
	  pp_cxx_left_paren (pp);
	pp_c_constant (pp_c_base (pp), t);
	if (in_parens)
	  pp_cxx_right_paren (pp);
      }
      break;

    default:
      pp_c_constant (pp_c_base (pp), t);
      break;
    }
}