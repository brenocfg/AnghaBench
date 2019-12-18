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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  BASELINK 131 
 int /*<<< orphan*/  BASELINK_FUNCTIONS (int /*<<< orphan*/ ) ; 
#define  EMPTY_CLASS_EXPR 130 
 int EXPAND_NORMAL ; 
 int EXPAND_SUM ; 
#define  OFFSET_REF 129 
#define  PTRMEM_CST 128 
 int Pmode ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  cplus_expand_constant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

rtx
cxx_expand_expr (tree exp, rtx target, enum machine_mode tmode, int modifier,
		 rtx *alt_rtl)
{
  tree type = TREE_TYPE (exp);
  enum machine_mode mode = TYPE_MODE (type);
  enum tree_code code = TREE_CODE (exp);

  /* No sense saving up arithmetic to be done
     if it's all in the wrong mode to form part of an address.
     And force_operand won't know whether to sign-extend or zero-extend.  */

  if (mode != Pmode && modifier == EXPAND_SUM)
    modifier = EXPAND_NORMAL;

  switch (code)
    {
    case PTRMEM_CST:
      return expand_expr (cplus_expand_constant (exp),
			  target, tmode, modifier);

    case OFFSET_REF:
      /* Offset refs should not make it through to here.  */
      gcc_unreachable ();

    case EMPTY_CLASS_EXPR:
      /* We don't need to generate any code for an empty class.  */
      return const0_rtx;

    case BASELINK:
      return expand_expr (BASELINK_FUNCTIONS (exp), target, tmode,
			  modifier);

    default:
      return c_expand_expr (exp, target, tmode, modifier, alt_rtl);
    }
}