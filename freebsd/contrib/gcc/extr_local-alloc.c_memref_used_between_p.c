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
 scalar_t__ CALL_P (scalar_t__) ; 
 int /*<<< orphan*/  CONST_OR_PURE_CALL_P (scalar_t__) ; 
 int /*<<< orphan*/  INSN_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ memref_referenced_p (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pure_call_p (scalar_t__) ; 

__attribute__((used)) static int
memref_used_between_p (rtx memref, rtx start, rtx end)
{
  rtx insn;

  for (insn = NEXT_INSN (start); insn != NEXT_INSN (end);
       insn = NEXT_INSN (insn))
    {
      if (!INSN_P (insn))
	continue;
      
      if (memref_referenced_p (memref, PATTERN (insn)))
	return 1;

      /* Nonconst functions may access memory.  */
      if (CALL_P (insn)
	  && (! CONST_OR_PURE_CALL_P (insn)
	      || pure_call_p (insn)))
	return 1;
    }

  return 0;
}