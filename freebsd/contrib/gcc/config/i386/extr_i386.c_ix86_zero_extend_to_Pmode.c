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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ Pmode ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  copy_to_mode_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (scalar_t__) ; 
 int /*<<< orphan*/  gen_zero_extendsidi2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
ix86_zero_extend_to_Pmode (rtx exp)
{
  rtx r;
  if (GET_MODE (exp) == VOIDmode)
    return force_reg (Pmode, exp);
  if (GET_MODE (exp) == Pmode)
    return copy_to_mode_reg (Pmode, exp);
  r = gen_reg_rtx (Pmode);
  emit_insn (gen_zero_extendsidi2 (r, exp));
  return r;
}