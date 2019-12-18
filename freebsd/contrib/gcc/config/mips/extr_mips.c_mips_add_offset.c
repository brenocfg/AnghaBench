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
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST_HIGH_PART (scalar_t__) ; 
 scalar_t__ CONST_LOW_PART (scalar_t__) ; 
 int /*<<< orphan*/  GEN_INT (scalar_t__) ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SMALL_OPERAND (scalar_t__) ; 
 scalar_t__ TARGET_MIPS16 ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_force_temporary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static rtx
mips_add_offset (rtx temp, rtx reg, HOST_WIDE_INT offset)
{
  if (!SMALL_OPERAND (offset))
    {
      rtx high;
      if (TARGET_MIPS16)
	{
	  /* Load the full offset into a register so that we can use
	     an unextended instruction for the address itself.  */
	  high = GEN_INT (offset);
	  offset = 0;
	}
      else
	{
	  /* Leave OFFSET as a 16-bit offset and put the excess in HIGH.  */
	  high = GEN_INT (CONST_HIGH_PART (offset));
	  offset = CONST_LOW_PART (offset);
	}
      high = mips_force_temporary (temp, high);
      reg = mips_force_temporary (temp, gen_rtx_PLUS (Pmode, high, reg));
    }
  return plus_constant (reg, offset);
}