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
 scalar_t__ INSN_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fatal_insn (char*,int /*<<< orphan*/ ,char const*,int,char const*) ; 

void
_fatal_insn_not_found (rtx insn, const char *file, int line,
		       const char *function)
{
  if (INSN_CODE (insn) < 0)
    _fatal_insn ("unrecognizable insn:", insn, file, line, function);
  else
    _fatal_insn ("insn does not satisfy its constraints:",
		insn, file, line, function);
}