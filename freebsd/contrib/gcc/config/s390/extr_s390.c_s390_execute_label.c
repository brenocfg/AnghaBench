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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ UNSPEC ; 
 scalar_t__ UNSPEC_EXECUTE ; 
 scalar_t__ XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
s390_execute_label (rtx insn)
{
  if (GET_CODE (insn) == INSN
      && GET_CODE (PATTERN (insn)) == PARALLEL
      && GET_CODE (XVECEXP (PATTERN (insn), 0, 0)) == UNSPEC
      && XINT (XVECEXP (PATTERN (insn), 0, 0), 1) == UNSPEC_EXECUTE)
    return XVECEXP (XVECEXP (PATTERN (insn), 0, 0), 0, 2);

  return NULL_RTX;
}