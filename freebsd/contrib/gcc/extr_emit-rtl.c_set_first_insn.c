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
 int /*<<< orphan*/  PREV_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_insn ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

void
set_first_insn (rtx insn)
{
  gcc_assert (!PREV_INSN (insn));
  first_insn = insn;
}