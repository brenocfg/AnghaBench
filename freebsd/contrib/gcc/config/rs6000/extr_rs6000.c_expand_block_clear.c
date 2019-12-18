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
 int /*<<< orphan*/  CONST0_RTX (int) ; 
 scalar_t__ CONST_INT ; 
 int DImode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int HImode ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int QImode ; 
 int SImode ; 
 int /*<<< orphan*/  STRICT_ALIGNMENT ; 
 scalar_t__ TARGET_ALTIVEC ; 
 scalar_t__ TARGET_POWERPC64 ; 
 int V4SImode ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ optimize_size ; 

int
expand_block_clear (rtx operands[])
{
  rtx orig_dest = operands[0];
  rtx bytes_rtx	= operands[1];
  rtx align_rtx = operands[3];
  bool constp	= (GET_CODE (bytes_rtx) == CONST_INT);
  HOST_WIDE_INT align;
  HOST_WIDE_INT bytes;
  int offset;
  int clear_bytes;
  int clear_step;

  /* If this is not a fixed size move, just call memcpy */
  if (! constp)
    return 0;

  /* This must be a fixed size alignment  */
  gcc_assert (GET_CODE (align_rtx) == CONST_INT);
  align = INTVAL (align_rtx) * BITS_PER_UNIT;

  /* Anything to clear? */
  bytes = INTVAL (bytes_rtx);
  if (bytes <= 0)
    return 1;

  /* Use the builtin memset after a point, to avoid huge code bloat.
     When optimize_size, avoid any significant code bloat; calling
     memset is about 4 instructions, so allow for one instruction to
     load zero and three to do clearing.  */
  if (TARGET_ALTIVEC && align >= 128)
    clear_step = 16;
  else if (TARGET_POWERPC64 && align >= 32)
    clear_step = 8;
  else
    clear_step = 4;

  if (optimize_size && bytes > 3 * clear_step)
    return 0;
  if (! optimize_size && bytes > 8 * clear_step)
    return 0;

  for (offset = 0; bytes > 0; offset += clear_bytes, bytes -= clear_bytes)
    {
      enum machine_mode mode = BLKmode;
      rtx dest;

      if (bytes >= 16 && TARGET_ALTIVEC && align >= 128)
	{
	  clear_bytes = 16;
	  mode = V4SImode;
	}
      else if (bytes >= 8 && TARGET_POWERPC64
	  /* 64-bit loads and stores require word-aligned
	     displacements.  */
	  && (align >= 64 || (!STRICT_ALIGNMENT && align >= 32)))
	{
	  clear_bytes = 8;
	  mode = DImode;
	}
      else if (bytes >= 4 && (align >= 32 || !STRICT_ALIGNMENT))
	{			/* move 4 bytes */
	  clear_bytes = 4;
	  mode = SImode;
	}
      else if (bytes >= 2 && (align >= 16 || !STRICT_ALIGNMENT))
	{			/* move 2 bytes */
	  clear_bytes = 2;
	  mode = HImode;
	}
      else /* move 1 byte at a time */
	{
	  clear_bytes = 1;
	  mode = QImode;
	}

      dest = adjust_address (orig_dest, mode, offset);

      emit_move_insn (dest, CONST0_RTX (mode));
    }

  return 1;
}