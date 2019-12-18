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
 scalar_t__ CALL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ JUMP_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NONJUMP_INSN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ USE ; 
 int /*<<< orphan*/  reload_completed ; 

int
active_insn_p (rtx insn)
{
  return (CALL_P (insn) || JUMP_P (insn)
	  || (NONJUMP_INSN_P (insn)
	      && (! reload_completed
		  || (GET_CODE (PATTERN (insn)) != USE
		      && GET_CODE (PATTERN (insn)) != CLOBBER))));
}