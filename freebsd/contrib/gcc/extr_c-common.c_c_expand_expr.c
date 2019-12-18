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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  COMPOUND_LITERAL_EXPR 128 
 int /*<<< orphan*/  COMPOUND_LITERAL_EXPR_DECL (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_local_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_expr_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

rtx
c_expand_expr (tree exp, rtx target, enum machine_mode tmode,
	       int modifier /* Actually enum_modifier.  */,
	       rtx *alt_rtl)
{
  switch (TREE_CODE (exp))
    {
    case COMPOUND_LITERAL_EXPR:
      {
	/* Initialize the anonymous variable declared in the compound
	   literal, then return the variable.  */
	tree decl = COMPOUND_LITERAL_EXPR_DECL (exp);
	emit_local_var (decl);
	return expand_expr_real (decl, target, tmode, modifier, alt_rtl);
      }

    default:
      gcc_unreachable ();
    }
}