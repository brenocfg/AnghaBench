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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_4__ {TYPE_1__* operand; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  (* predicate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  convert_modes (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_to_mode_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* insn_data ; 
 scalar_t__ no_new_pseudos ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
prepare_operand (int icode, rtx x, int opnum, enum machine_mode mode,
		 enum machine_mode wider_mode, int unsignedp)
{
  if (mode != wider_mode)
    x = convert_modes (wider_mode, mode, x, unsignedp);

  if (!insn_data[icode].operand[opnum].predicate
      (x, insn_data[icode].operand[opnum].mode))
    {
      if (no_new_pseudos)
	return NULL_RTX;
      x = copy_to_mode_reg (insn_data[icode].operand[opnum].mode, x);
    }

  return x;
}