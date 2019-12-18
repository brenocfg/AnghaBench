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
#define  BARRIER 134 
#define  CALL_INSN 133 
#define  CODE_LABEL 132 
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  INSN 131 
#define  JUMP_INSN 130 
#define  NOTE 129 
#define  SEQUENCE 128 
 int /*<<< orphan*/  add_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  make_call_insn_raw (int /*<<< orphan*/ ) ; 

rtx
emit_call_insn (rtx x)
{
  rtx insn;

  switch (GET_CODE (x))
    {
    case INSN:
    case JUMP_INSN:
    case CALL_INSN:
    case CODE_LABEL:
    case BARRIER:
    case NOTE:
      insn = emit_insn (x);
      break;

#ifdef ENABLE_RTL_CHECKING
    case SEQUENCE:
      gcc_unreachable ();
      break;
#endif

    default:
      insn = make_call_insn_raw (x);
      add_insn (insn);
      break;
    }

  return insn;
}