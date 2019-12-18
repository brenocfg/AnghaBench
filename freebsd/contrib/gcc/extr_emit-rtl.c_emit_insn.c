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
typedef  scalar_t__ rtx ;

/* Variables and functions */
#define  BARRIER 134 
#define  CALL_INSN 133 
#define  CODE_LABEL 132 
 int GET_CODE (scalar_t__) ; 
#define  INSN 131 
#define  JUMP_INSN 130 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
#define  NOTE 129 
 scalar_t__ NULL_RTX ; 
#define  SEQUENCE 128 
 int /*<<< orphan*/  add_insn (scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ last_insn ; 
 scalar_t__ make_insn_raw (scalar_t__) ; 

rtx
emit_insn (rtx x)
{
  rtx last = last_insn;
  rtx insn;

  if (x == NULL_RTX)
    return last;

  switch (GET_CODE (x))
    {
    case INSN:
    case JUMP_INSN:
    case CALL_INSN:
    case CODE_LABEL:
    case BARRIER:
    case NOTE:
      insn = x;
      while (insn)
	{
	  rtx next = NEXT_INSN (insn);
	  add_insn (insn);
	  last = insn;
	  insn = next;
	}
      break;

#ifdef ENABLE_RTL_CHECKING
    case SEQUENCE:
      gcc_unreachable ();
      break;
#endif

    default:
      last = make_insn_raw (x);
      add_insn (last);
      break;
    }

  return last;
}