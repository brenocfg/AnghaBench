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
 scalar_t__ JUMP_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NONJUMP_INSN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ RETURN ; 
 scalar_t__ SEQUENCE ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
return_insn_p (rtx insn)
{
  if (JUMP_P (insn) && GET_CODE (PATTERN (insn)) == RETURN)
    return true;

  if (NONJUMP_INSN_P (insn) && GET_CODE (PATTERN (insn)) == SEQUENCE)
    return return_insn_p (XVECEXP (PATTERN (insn), 0, 0));

  return false;
}