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
struct noce_if_info {int /*<<< orphan*/  cond; int /*<<< orphan*/  x; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ JUMP_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ get_insns () ; 
 int recog_memoized (scalar_t__) ; 
 int /*<<< orphan*/  set_used_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unshare_all_rtl_in_chain (scalar_t__) ; 

__attribute__((used)) static rtx
end_ifcvt_sequence (struct noce_if_info *if_info)
{
  rtx insn;
  rtx seq = get_insns ();

  set_used_flags (if_info->x);
  set_used_flags (if_info->cond);
  unshare_all_rtl_in_chain (seq);
  end_sequence ();

  /* Make sure that all of the instructions emitted are recognizable,
     and that we haven't introduced a new jump instruction.
     As an exercise for the reader, build a general mechanism that
     allows proper placement of required clobbers.  */
  for (insn = seq; insn; insn = NEXT_INSN (insn))
    if (JUMP_P (insn)
	|| recog_memoized (insn) == -1)
      return NULL_RTX;

  return seq;
}