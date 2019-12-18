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
 int /*<<< orphan*/ * TREE_CHAIN (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_NOTHROW_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_RAISES_EXCEPTIONS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_cxx_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_separate_with (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_cxx_type_id (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
pp_cxx_exception_specification (cxx_pretty_printer *pp, tree t)
{
  tree ex_spec = TYPE_RAISES_EXCEPTIONS (t);

  if (!TYPE_NOTHROW_P (t) && ex_spec == NULL)
    return;
  pp_cxx_identifier (pp, "throw");
  pp_cxx_left_paren (pp);
  for (; ex_spec && TREE_VALUE (ex_spec); ex_spec = TREE_CHAIN (ex_spec))
    {
      pp_cxx_type_id (pp, TREE_VALUE (ex_spec));
      if (TREE_CHAIN (ex_spec))
	pp_cxx_separate_with (pp, ',');
    }
  pp_cxx_right_paren (pp);
}