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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NONJUMP_INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ SEQUENCE ; 
 scalar_t__ XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
next_insn (rtx insn)
{
  if (insn)
    {
      insn = NEXT_INSN (insn);
      if (insn && NONJUMP_INSN_P (insn)
	  && GET_CODE (PATTERN (insn)) == SEQUENCE)
	insn = XVECEXP (PATTERN (insn), 0, 0);
    }

  return insn;
}