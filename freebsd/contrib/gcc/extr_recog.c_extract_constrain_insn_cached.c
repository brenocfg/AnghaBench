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
 int /*<<< orphan*/  constrain_operands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_insn_cached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_insn_not_found (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload_completed ; 
 int which_alternative ; 

void
extract_constrain_insn_cached (rtx insn)
{
  extract_insn_cached (insn);
  if (which_alternative == -1
      && !constrain_operands (reload_completed))
    fatal_insn_not_found (insn);
}