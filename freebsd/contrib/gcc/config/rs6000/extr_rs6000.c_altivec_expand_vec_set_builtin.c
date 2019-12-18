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
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VECTOR_MODE_P (int) ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  convert_modes (int,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int get_element_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs6000_expand_vector_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
altivec_expand_vec_set_builtin (tree arglist)
{
  enum machine_mode tmode, mode1;
  tree arg0, arg1, arg2;
  int elt;
  rtx op0, op1;

  arg0 = TREE_VALUE (arglist);
  arg1 = TREE_VALUE (TREE_CHAIN (arglist));
  arg2 = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));

  tmode = TYPE_MODE (TREE_TYPE (arg0));
  mode1 = TYPE_MODE (TREE_TYPE (TREE_TYPE (arg0)));
  gcc_assert (VECTOR_MODE_P (tmode));

  op0 = expand_expr (arg0, NULL_RTX, tmode, 0);
  op1 = expand_expr (arg1, NULL_RTX, mode1, 0);
  elt = get_element_number (TREE_TYPE (arg0), arg2);

  if (GET_MODE (op1) != mode1 && GET_MODE (op1) != VOIDmode)
    op1 = convert_modes (mode1, GET_MODE (op1), op1, true);

  op0 = force_reg (tmode, op0);
  op1 = force_reg (mode1, op1);

  rs6000_expand_vector_set (op0, op1, elt);

  return op0;
}