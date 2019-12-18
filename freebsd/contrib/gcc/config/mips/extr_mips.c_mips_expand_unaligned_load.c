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
 scalar_t__ DImode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 unsigned int GET_MODE_BITSIZE (scalar_t__) ; 
 scalar_t__ SImode ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mov_ldl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mov_ldr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mov_lwl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mov_lwr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (scalar_t__) ; 
 int /*<<< orphan*/  mips_get_unaligned_mem (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
mips_expand_unaligned_load (rtx dest, rtx src, unsigned int width, int bitpos)
{
  rtx left, right, temp;

  /* If TARGET_64BIT, the destination of a 32-bit load will be a
     paradoxical word_mode subreg.  This is the only case in which
     we allow the destination to be larger than the source.  */
  if (GET_CODE (dest) == SUBREG
      && GET_MODE (dest) == DImode
      && SUBREG_BYTE (dest) == 0
      && GET_MODE (SUBREG_REG (dest)) == SImode)
    dest = SUBREG_REG (dest);

  /* After the above adjustment, the destination must be the same
     width as the source.  */
  if (GET_MODE_BITSIZE (GET_MODE (dest)) != width)
    return false;

  if (!mips_get_unaligned_mem (&src, width, bitpos, &left, &right))
    return false;

  temp = gen_reg_rtx (GET_MODE (dest));
  if (GET_MODE (dest) == DImode)
    {
      emit_insn (gen_mov_ldl (temp, src, left));
      emit_insn (gen_mov_ldr (dest, copy_rtx (src), right, temp));
    }
  else
    {
      emit_insn (gen_mov_lwl (temp, src, left));
      emit_insn (gen_mov_lwr (dest, copy_rtx (src), right, temp));
    }
  return true;
}