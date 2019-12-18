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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TLS_SYMBOLIC_CONST (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_pic ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legitimize_pic_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legitimize_tls_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ no_new_pseudos ; 

void
emit_symbolic_move (rtx *operands)
{
  rtx temp = no_new_pseudos ? operands[0] : gen_reg_rtx (Pmode);

  if (GET_CODE (operands[0]) == MEM)
    operands[1] = force_reg (Pmode, operands[1]);
  else if (TLS_SYMBOLIC_CONST (operands[1]))
    operands[1] = legitimize_tls_address (operands[1], temp);
  else if (flag_pic)
    operands[1] = legitimize_pic_address (operands[1], temp);
}