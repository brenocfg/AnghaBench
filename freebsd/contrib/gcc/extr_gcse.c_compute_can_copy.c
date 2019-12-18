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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ LAST_VIRTUAL_REGISTER ; 
 scalar_t__ MODE_CC ; 
 int NUM_MACHINE_MODES ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int* can_copy ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  gen_rtx_REG (int,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ recog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static void
compute_can_copy (void)
{
  int i;
#ifndef AVOID_CCMODE_COPIES
  rtx reg, insn;
#endif
  memset (can_copy, 0, NUM_MACHINE_MODES);

  start_sequence ();
  for (i = 0; i < NUM_MACHINE_MODES; i++)
    if (GET_MODE_CLASS (i) == MODE_CC)
      {
#ifdef AVOID_CCMODE_COPIES
	can_copy[i] = 0;
#else
	reg = gen_rtx_REG ((enum machine_mode) i, LAST_VIRTUAL_REGISTER + 1);
	insn = emit_insn (gen_rtx_SET (VOIDmode, reg, reg));
	if (recog (PATTERN (insn), insn, NULL) >= 0)
	  can_copy[i] = 1;
#endif
      }
    else
      can_copy[i] = 1;

  end_sequence ();
}