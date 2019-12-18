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
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VECTOR_MODE_P (int) ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int get_element_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  register_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rs6000_expand_vector_extract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
altivec_expand_vec_ext_builtin (tree arglist, rtx target)
{
  enum machine_mode tmode, mode0;
  tree arg0, arg1;
  int elt;
  rtx op0;

  arg0 = TREE_VALUE (arglist);
  arg1 = TREE_VALUE (TREE_CHAIN (arglist));

  op0 = expand_normal (arg0);
  elt = get_element_number (TREE_TYPE (arg0), arg1);

  tmode = TYPE_MODE (TREE_TYPE (TREE_TYPE (arg0)));
  mode0 = TYPE_MODE (TREE_TYPE (arg0));
  gcc_assert (VECTOR_MODE_P (mode0));

  op0 = force_reg (mode0, op0);

  if (optimize || !target || !register_operand (target, tmode))
    target = gen_reg_rtx (tmode);

  rs6000_expand_vector_extract (target, op0, elt);

  return target;
}