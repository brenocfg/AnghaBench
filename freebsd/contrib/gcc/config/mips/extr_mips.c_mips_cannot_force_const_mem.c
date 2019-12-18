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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ SMALL_OPERAND (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_HAVE_TLS ; 
 int /*<<< orphan*/  TARGET_MIPS16 ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ for_each_rtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_split_const (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mips_tls_symbol_ref_1 ; 
 scalar_t__ symbolic_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mips_cannot_force_const_mem (rtx x)
{
  rtx base;
  HOST_WIDE_INT offset;

  if (!TARGET_MIPS16)
    {
      /* As an optimization, reject constants that mips_legitimize_move
	 can expand inline.

	 Suppose we have a multi-instruction sequence that loads constant C
	 into register R.  If R does not get allocated a hard register, and
	 R is used in an operand that allows both registers and memory
	 references, reload will consider forcing C into memory and using
	 one of the instruction's memory alternatives.  Returning false
	 here will force it to use an input reload instead.  */
      if (GET_CODE (x) == CONST_INT)
	return true;

      mips_split_const (x, &base, &offset);
      if (symbolic_operand (base, VOIDmode) && SMALL_OPERAND (offset))
	return true;
    }

  if (TARGET_HAVE_TLS && for_each_rtx (&x, &mips_tls_symbol_ref_1, 0))
    return true;

  return false;
}