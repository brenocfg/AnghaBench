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
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_INNER (int) ; 
 unsigned int GET_MODE_SIZE (int) ; 
#define  POST_DEC 131 
#define  POST_INC 130 
#define  PRE_DEC 129 
#define  PRE_INC 128 
 unsigned int PUSH_ROUNDING (unsigned int) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_resolve_push (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_rtx_MEM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_complex_part (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
emit_move_complex_push (enum machine_mode mode, rtx x, rtx y)
{
  enum machine_mode submode = GET_MODE_INNER (mode);
  bool imag_first;

#ifdef PUSH_ROUNDING
  unsigned int submodesize = GET_MODE_SIZE (submode);

  /* In case we output to the stack, but the size is smaller than the
     machine can push exactly, we need to use move instructions.  */
  if (PUSH_ROUNDING (submodesize) != submodesize)
    {
      x = emit_move_resolve_push (mode, x);
      return emit_move_insn (x, y);
    }
#endif

  /* Note that the real part always precedes the imag part in memory
     regardless of machine's endianness.  */
  switch (GET_CODE (XEXP (x, 0)))
    {
    case PRE_DEC:
    case POST_DEC:
      imag_first = true;
      break;
    case PRE_INC:
    case POST_INC:
      imag_first = false;
      break;
    default:
      gcc_unreachable ();
    }

  emit_move_insn (gen_rtx_MEM (submode, XEXP (x, 0)),
		  read_complex_part (y, imag_first));
  return emit_move_insn (gen_rtx_MEM (submode, XEXP (x, 0)),
			 read_complex_part (y, !imag_first));
}