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
 int /*<<< orphan*/  DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NONCONVERTING_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_VIRTUAL_P (int /*<<< orphan*/ ) ; 
#define  FUNCTION_DECL 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_function_specifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
pp_cxx_function_specifier (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
    case FUNCTION_DECL:
      if (DECL_VIRTUAL_P (t))
	pp_cxx_identifier (pp, "virtual");
      else if (DECL_CONSTRUCTOR_P (t) && DECL_NONCONVERTING_P (t))
	pp_cxx_identifier (pp, "explicit");
      else
	pp_c_function_specifier (pp_c_base (pp), t);

    default:
      break;
    }
}