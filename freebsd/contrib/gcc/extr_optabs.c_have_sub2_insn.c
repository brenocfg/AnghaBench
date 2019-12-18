#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_8__ {TYPE_2__* operand; } ;
struct TYPE_7__ {TYPE_1__* handlers; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  (* predicate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ insn_code; } ;

/* Variables and functions */
 int CODE_FOR_nothing ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_4__* insn_data ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* sub_optab ; 

int
have_sub2_insn (rtx x, rtx y)
{
  int icode;

  gcc_assert (GET_MODE (x) != VOIDmode);

  icode = (int) sub_optab->handlers[(int) GET_MODE (x)].insn_code;

  if (icode == CODE_FOR_nothing)
    return 0;

  if (!(insn_data[icode].operand[0].predicate
	(x, insn_data[icode].operand[0].mode))
      || !(insn_data[icode].operand[1].predicate
	   (x, insn_data[icode].operand[1].mode))
      || !(insn_data[icode].operand[2].predicate
	   (y, insn_data[icode].operand[2].mode)))
    return 0;

  return 1;
}