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
 scalar_t__ BIT_XOR_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pp_c_and_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_maybe_whitespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_whitespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_carret (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_c_exclusive_or_expression (c_pretty_printer *pp, tree e)
{
  if (TREE_CODE (e) == BIT_XOR_EXPR)
    {
      pp_c_exclusive_or_expression (pp, TREE_OPERAND (e, 0));
      pp_c_maybe_whitespace (pp);
      pp_carret (pp);
      pp_c_whitespace (pp);
      pp_c_and_expression (pp, TREE_OPERAND (e, 1));
    }
  else
    pp_c_and_expression (pp, e);
}