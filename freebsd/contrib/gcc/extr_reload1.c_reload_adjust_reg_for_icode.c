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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
struct TYPE_4__ {TYPE_1__* operand; } ;
struct TYPE_3__ {int mode; } ;

/* Variables and functions */
 TYPE_2__* insn_data ; 
 int reload_adjust_reg_for_temp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int scratch_reload_class (int) ; 

__attribute__((used)) static bool
reload_adjust_reg_for_icode (rtx *reload_reg, rtx alt_reload_reg,
			     enum insn_code icode)

{
  enum reg_class new_class = scratch_reload_class (icode);
  enum machine_mode new_mode = insn_data[(int) icode].operand[2].mode;

  return reload_adjust_reg_for_temp (reload_reg, alt_reload_reg,
				     new_class, new_mode);
}