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
 int /*<<< orphan*/  CONST_DOUBLE_FROM_REAL_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFmode ; 
 int /*<<< orphan*/  SFmode ; 
 int /*<<< orphan*/  UNSPEC_FRES ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  dconst1 ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MINUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MULT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_UNSPEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
rs6000_emit_swdivdf (rtx res, rtx n, rtx d)
{
  rtx x0, e0, e1, e2, y1, y2, y3, u0, v0, one;

  x0 = gen_reg_rtx (DFmode);
  e0 = gen_reg_rtx (DFmode);
  e1 = gen_reg_rtx (DFmode);
  e2 = gen_reg_rtx (DFmode);
  y1 = gen_reg_rtx (DFmode);
  y2 = gen_reg_rtx (DFmode);
  y3 = gen_reg_rtx (DFmode);
  u0 = gen_reg_rtx (DFmode);
  v0 = gen_reg_rtx (DFmode);
  one = force_reg (DFmode, CONST_DOUBLE_FROM_REAL_VALUE (dconst1, DFmode));

  /* x0 = 1./d estimate */
  emit_insn (gen_rtx_SET (VOIDmode, x0,
			  gen_rtx_UNSPEC (DFmode, gen_rtvec (1, d),
					  UNSPEC_FRES)));
  /* e0 = 1. - d * x0 */
  emit_insn (gen_rtx_SET (VOIDmode, e0,
			  gen_rtx_MINUS (DFmode, one,
					 gen_rtx_MULT (SFmode, d, x0))));
  /* y1 = x0 + e0 * x0 */
  emit_insn (gen_rtx_SET (VOIDmode, y1,
			  gen_rtx_PLUS (DFmode,
					gen_rtx_MULT (DFmode, e0, x0), x0)));
  /* e1 = e0 * e0 */
  emit_insn (gen_rtx_SET (VOIDmode, e1,
			  gen_rtx_MULT (DFmode, e0, e0)));
  /* y2 = y1 + e1 * y1 */
  emit_insn (gen_rtx_SET (VOIDmode, y2,
			  gen_rtx_PLUS (DFmode,
					gen_rtx_MULT (DFmode, e1, y1), y1)));
  /* e2 = e1 * e1 */
  emit_insn (gen_rtx_SET (VOIDmode, e2,
			  gen_rtx_MULT (DFmode, e1, e1)));
  /* y3 = y2 + e2 * y2 */
  emit_insn (gen_rtx_SET (VOIDmode, y3,
			  gen_rtx_PLUS (DFmode,
					gen_rtx_MULT (DFmode, e2, y2), y2)));
  /* u0 = n * y3 */
  emit_insn (gen_rtx_SET (VOIDmode, u0,
			  gen_rtx_MULT (DFmode, n, y3)));
  /* v0 = n - d * u0 */
  emit_insn (gen_rtx_SET (VOIDmode, v0,
			  gen_rtx_MINUS (DFmode, n,
					 gen_rtx_MULT (DFmode, d, u0))));
  /* res = u0 + v0 * y3 */
  emit_insn (gen_rtx_SET (VOIDmode, res,
			  gen_rtx_PLUS (DFmode,
					gen_rtx_MULT (DFmode, v0, y3), u0)));
}