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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_UNSPEC (int,int /*<<< orphan*/ ,int) ; 
 int get_vsel_insn (int) ; 

__attribute__((used)) static void
rs6000_emit_vector_select (rtx dest, rtx op1, rtx op2, rtx mask)
{
  rtx t, temp;
  enum machine_mode dest_mode = GET_MODE (dest);
  int vsel_insn_index  = get_vsel_insn (GET_MODE (dest));

  temp = gen_reg_rtx (dest_mode);

  /* For each vector element, select op1 when mask is 1 otherwise
     select op2.  */
  t = gen_rtx_SET (VOIDmode, temp,
		   gen_rtx_UNSPEC (dest_mode,
				   gen_rtvec (3, op2, op1, mask),
				   vsel_insn_index));
  emit_insn (t);
  emit_move_insn (dest, temp);
  return;
}