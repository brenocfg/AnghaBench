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

/* Variables and functions */
 int TFF_EXPR_IN_PARENS ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_expr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pp_cxx_left_paren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_right_paren (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_unary_op (const char *opstring, tree t, int flags)
{
  if (flags & TFF_EXPR_IN_PARENS)
    pp_cxx_left_paren (cxx_pp);
  pp_cxx_identifier (cxx_pp, opstring);
  dump_expr (TREE_OPERAND (t, 0), flags & ~TFF_EXPR_IN_PARENS);
  if (flags & TFF_EXPR_IN_PARENS)
    pp_cxx_right_paren (cxx_pp);
}