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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
#define  CALL_INSN 131 
#define  CODE_LABEL 130 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
#define  INSN 129 
#define  JUMP_INSN 128 
 int /*<<< orphan*/  RETURN ; 
 int /*<<< orphan*/  any_uncondjump_p (int /*<<< orphan*/ ) ; 
 int classify_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_call_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

rtx
emit (rtx x)
{
  enum rtx_code code = classify_insn (x);

  switch (code)
    {
    case CODE_LABEL:
      return emit_label (x);
    case INSN:
      return emit_insn (x);
    case  JUMP_INSN:
      {
	rtx insn = emit_jump_insn (x);
	if (any_uncondjump_p (insn) || GET_CODE (x) == RETURN)
	  return emit_barrier ();
	return insn;
      }
    case CALL_INSN:
      return emit_call_insn (x);
    default:
      gcc_unreachable ();
    }
}