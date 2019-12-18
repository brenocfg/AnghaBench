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
 int /*<<< orphan*/  emit_jump_insn_after_noloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn_after_setloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
emit_jump_insn_after (rtx pattern, rtx after)
{
  if (INSN_P (after))
    return emit_jump_insn_after_setloc (pattern, after, INSN_LOCATOR (after));
  else
    return emit_jump_insn_after_noloc (pattern, after);
}