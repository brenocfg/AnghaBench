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
 scalar_t__ ADDR_DIFF_VEC ; 
 scalar_t__ ADDR_VEC ; 
 scalar_t__ CALL_INSN ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_P (int /*<<< orphan*/ ) ; 
 scalar_t__ JUMP_INSN ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIBLING_CALL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ UNSPECV_ALIGN ; 
 scalar_t__ UNSPEC_VOLATILE ; 
 scalar_t__ XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  active_insn_p (int /*<<< orphan*/ ) ; 
 int get_attr_length (int /*<<< orphan*/ ) ; 
 int get_attr_length_address (int /*<<< orphan*/ ) ; 
 scalar_t__ symbolic_reference_mentioned_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
min_insn_size (rtx insn)
{
  int l = 0;

  if (!INSN_P (insn) || !active_insn_p (insn))
    return 0;

  /* Discard alignments we've emit and jump instructions.  */
  if (GET_CODE (PATTERN (insn)) == UNSPEC_VOLATILE
      && XINT (PATTERN (insn), 1) == UNSPECV_ALIGN)
    return 0;
  if (GET_CODE (insn) == JUMP_INSN
      && (GET_CODE (PATTERN (insn)) == ADDR_VEC
	  || GET_CODE (PATTERN (insn)) == ADDR_DIFF_VEC))
    return 0;

  /* Important case - calls are always 5 bytes.
     It is common to have many calls in the row.  */
  if (GET_CODE (insn) == CALL_INSN
      && symbolic_reference_mentioned_p (PATTERN (insn))
      && !SIBLING_CALL_P (insn))
    return 5;
  if (get_attr_length (insn) <= 1)
    return 1;

  /* For normal instructions we may rely on the sizes of addresses
     and the presence of symbol to require 4 bytes of encoding.
     This is not the case for jumps where references are PC relative.  */
  if (GET_CODE (insn) != JUMP_INSN)
    {
      l = get_attr_length_address (insn);
      if (l < 4 && symbolic_reference_mentioned_p (PATTERN (insn)))
	l = 4;
    }
  if (l)
    return 1+l;
  else
    return 2;
}