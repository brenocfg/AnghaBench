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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
#define  LSHIFT_EXPR 129 
#define  RSHIFT_EXPR 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pp_c_additive_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_whitespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_identifier (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
pp_c_shift_expression (c_pretty_printer *pp, tree e)
{
  enum tree_code code = TREE_CODE (e);
  switch (code)
    {
    case LSHIFT_EXPR:
    case RSHIFT_EXPR:
      pp_c_shift_expression (pp, TREE_OPERAND (e, 0));
      pp_c_whitespace (pp);
      pp_identifier (pp, code == LSHIFT_EXPR ? "<<" : ">>");
      pp_c_whitespace (pp);
      pp_c_additive_expression (pp, TREE_OPERAND (e, 1));
      break;

    default:
      pp_c_additive_expression (pp, e);
    }
}