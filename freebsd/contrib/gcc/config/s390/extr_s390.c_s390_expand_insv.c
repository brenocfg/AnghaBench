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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int BLKmode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int GET_MODE_BITSIZE (int) ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int HImode ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODE_INT ; 
 int SImode ; 
 scalar_t__ TARGET_EXTIMM ; 
 scalar_t__ TARGET_ZARCH ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 scalar_t__ const_int_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_const_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_int_mode (int,int) ; 
 int /*<<< orphan*/  gen_lowpart (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LSHIFTRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_ZERO_EXTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memory_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ register_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_expand_movmem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mem_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smallest_mode_for_size (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  word_mode ; 

bool 
s390_expand_insv (rtx dest, rtx op1, rtx op2, rtx src)
{
  int bitsize = INTVAL (op1);
  int bitpos = INTVAL (op2);

  /* We need byte alignment.  */
  if (bitsize % BITS_PER_UNIT)
    return false;

  if (bitpos == 0
      && memory_operand (dest, VOIDmode)
      && (register_operand (src, word_mode)
	  || const_int_operand (src, VOIDmode)))
    {
      /* Emit standard pattern if possible.  */
      enum machine_mode mode = smallest_mode_for_size (bitsize, MODE_INT);
      if (GET_MODE_BITSIZE (mode) == bitsize)
	emit_move_insn (adjust_address (dest, mode, 0), gen_lowpart (mode, src));

      /* (set (ze (mem)) (const_int)).  */
      else if (const_int_operand (src, VOIDmode))
	{
	  int size = bitsize / BITS_PER_UNIT;
	  rtx src_mem = adjust_address (force_const_mem (word_mode, src), BLKmode,
					GET_MODE_SIZE (word_mode) - size);

	  dest = adjust_address (dest, BLKmode, 0);
	  set_mem_size (dest, GEN_INT (size));
	  s390_expand_movmem (dest, src_mem, GEN_INT (size));
	}
	  
      /* (set (ze (mem)) (reg)).  */
      else if (register_operand (src, word_mode))
	{
	  if (bitsize <= GET_MODE_BITSIZE (SImode))
	    emit_move_insn (gen_rtx_ZERO_EXTRACT (word_mode, dest, op1,
						  const0_rtx), src);
	  else
	    {
	      /* Emit st,stcmh sequence.  */
	      int stcmh_width = bitsize - GET_MODE_BITSIZE (SImode);
	      int size = stcmh_width / BITS_PER_UNIT;

	      emit_move_insn (adjust_address (dest, SImode, size), 
			      gen_lowpart (SImode, src));
	      set_mem_size (dest, GEN_INT (size));
	      emit_move_insn (gen_rtx_ZERO_EXTRACT (word_mode, dest, GEN_INT
						    (stcmh_width), const0_rtx),
			      gen_rtx_LSHIFTRT (word_mode, src, GEN_INT
						(GET_MODE_BITSIZE (SImode))));
	    }
	}
      else
	return false;

      return true;
    }

  /* (set (ze (reg)) (const_int)).  */
  if (TARGET_ZARCH
      && register_operand (dest, word_mode) 
      && (bitpos % 16) == 0
      && (bitsize % 16) == 0
      && const_int_operand (src, VOIDmode))
    {
      HOST_WIDE_INT val = INTVAL (src);
      int regpos = bitpos + bitsize;

      while (regpos > bitpos)
	{
	  enum machine_mode putmode;
	  int putsize;

	  if (TARGET_EXTIMM && (regpos % 32 == 0) && (regpos >= bitpos + 32))
	    putmode = SImode;
	  else
	    putmode = HImode;

	  putsize = GET_MODE_BITSIZE (putmode);
	  regpos -= putsize;
	  emit_move_insn (gen_rtx_ZERO_EXTRACT (word_mode, dest, 
						GEN_INT (putsize),
						GEN_INT (regpos)), 
			  gen_int_mode (val, putmode));
	  val >>= putsize;
	}
      gcc_assert (regpos == bitpos);
      return true;
    }

  return false;
}