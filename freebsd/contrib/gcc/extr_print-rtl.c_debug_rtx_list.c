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
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 int /*<<< orphan*/  debug_rtx (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
debug_rtx_list (rtx x, int n)
{
  int i,count;
  rtx insn;

  count = n == 0 ? 1 : n < 0 ? -n : n;

  /* If we are printing a window, back up to the start.  */

  if (n < 0)
    for (i = count / 2; i > 0; i--)
      {
	if (PREV_INSN (x) == 0)
	  break;
	x = PREV_INSN (x);
      }

  for (i = count, insn = x; i > 0 && insn != 0; i--, insn = NEXT_INSN (insn))
    {
      debug_rtx (insn);
      fprintf (stderr, "\n");
    }
}