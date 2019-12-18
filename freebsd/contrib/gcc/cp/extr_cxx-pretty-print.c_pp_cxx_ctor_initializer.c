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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  pp_colon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_call_argument_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_primary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_separate_with (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_cxx_whitespace (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_cxx_ctor_initializer (cxx_pretty_printer *pp, tree t)
{
  t = TREE_OPERAND (t, 0);
  pp_cxx_whitespace (pp);
  pp_colon (pp);
  pp_cxx_whitespace (pp);
  for (; t; t = TREE_CHAIN (t))
    {
      pp_cxx_primary_expression (pp, TREE_PURPOSE (t));
      pp_cxx_call_argument_list (pp, TREE_VALUE (t));
      if (TREE_CHAIN (t))
	pp_cxx_separate_with (pp, ',');
    }
}