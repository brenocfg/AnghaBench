#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {int add; int shift_const; } ;

/* Variables and functions */
 int DImode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_adddi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_addsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_ashldi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_ashlsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ix86_cost ; 
 int /*<<< orphan*/  optimize_size ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ix86_expand_ashl_const (rtx operand, int count, enum machine_mode mode)
{
  if (count == 1)
    {
      emit_insn ((mode == DImode
		  ? gen_addsi3
		  : gen_adddi3) (operand, operand, operand));
    }
  else if (!optimize_size
	   && count * ix86_cost->add <= ix86_cost->shift_const)
    {
      int i;
      for (i=0; i<count; i++)
	{
	  emit_insn ((mode == DImode
		      ? gen_addsi3
		      : gen_adddi3) (operand, operand, operand));
	}
    }
  else
    emit_insn ((mode == DImode
		? gen_ashlsi3
		: gen_ashldi3) (operand, operand, GEN_INT (count)));
}