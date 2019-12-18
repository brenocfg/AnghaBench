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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ force_operand (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  general_operand (scalar_t__,int /*<<< orphan*/ ) ; 

rtx
copy_to_reg (rtx x)
{
  rtx temp = gen_reg_rtx (GET_MODE (x));

  /* If not an operand, must be an address with PLUS and MULT so
     do the computation.  */
  if (! general_operand (x, VOIDmode))
    x = force_operand (x, temp);

  if (x != temp)
    emit_move_insn (temp, x);

  return temp;
}