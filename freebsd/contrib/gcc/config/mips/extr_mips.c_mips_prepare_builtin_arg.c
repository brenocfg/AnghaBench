#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
struct TYPE_4__ {TYPE_1__* operand; } ;
struct TYPE_3__ {int mode; int /*<<< orphan*/  (* predicate ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  copy_to_mode_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 
 TYPE_2__* insn_data ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
mips_prepare_builtin_arg (enum insn_code icode,
			  unsigned int op, tree *arglist)
{
  rtx value;
  enum machine_mode mode;

  value = expand_normal (TREE_VALUE (*arglist));
  mode = insn_data[icode].operand[op].mode;
  if (!insn_data[icode].operand[op].predicate (value, mode))
    {
      value = copy_to_mode_reg (mode, value);
      /* Check the predicate again.  */
      if (!insn_data[icode].operand[op].predicate (value, mode))
	{
	  error ("invalid argument to builtin function");
	  return const0_rtx;
	}
    }

  *arglist = TREE_CHAIN (*arglist);
  return value;
}