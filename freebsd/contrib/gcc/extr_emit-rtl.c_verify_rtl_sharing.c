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
 scalar_t__ INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  LOG_LINKS (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  REG_NOTES (scalar_t__) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  reset_used_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_rtx_sharing (int /*<<< orphan*/ ,scalar_t__) ; 

void
verify_rtl_sharing (void)
{
  rtx p;

  for (p = get_insns (); p; p = NEXT_INSN (p))
    if (INSN_P (p))
      {
	reset_used_flags (PATTERN (p));
	reset_used_flags (REG_NOTES (p));
	reset_used_flags (LOG_LINKS (p));
      }

  for (p = get_insns (); p; p = NEXT_INSN (p))
    if (INSN_P (p))
      {
	verify_rtx_sharing (PATTERN (p), p);
	verify_rtx_sharing (REG_NOTES (p), p);
	verify_rtx_sharing (LOG_LINKS (p), p);
      }
}