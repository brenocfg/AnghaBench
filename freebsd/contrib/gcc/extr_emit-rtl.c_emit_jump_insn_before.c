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
 int /*<<< orphan*/  INSN_LOCATOR (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn_before_noloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn_before_setloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
emit_jump_insn_before (rtx pattern, rtx before)
{
  if (INSN_P (before))
    return emit_jump_insn_before_setloc (pattern, before, INSN_LOCATOR (before));
  else
    return emit_jump_insn_before_noloc (pattern, before);
}