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
 int /*<<< orphan*/  AND ; 
 int BITS_PER_UNIT ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 int /*<<< orphan*/  PLUS ; 
 int /*<<< orphan*/  Pmode ; 
 int STACK_BOUNDARY ; 
 int TRAMPOLINE_ALIGNMENT ; 
 int /*<<< orphan*/  expand_simple_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
round_trampoline_addr (rtx tramp)
{
  rtx temp, addend, mask;

  /* If we don't need too much alignment, we'll have been guaranteed
     proper alignment by get_trampoline_type.  */
  if (TRAMPOLINE_ALIGNMENT <= STACK_BOUNDARY)
    return tramp;

  /* Round address up to desired boundary.  */
  temp = gen_reg_rtx (Pmode);
  addend = GEN_INT (TRAMPOLINE_ALIGNMENT / BITS_PER_UNIT - 1);
  mask = GEN_INT (-TRAMPOLINE_ALIGNMENT / BITS_PER_UNIT);

  temp  = expand_simple_binop (Pmode, PLUS, tramp, addend,
			       temp, 0, OPTAB_LIB_WIDEN);
  tramp = expand_simple_binop (Pmode, AND, temp, mask,
			       temp, 0, OPTAB_LIB_WIDEN);

  return tramp;
}