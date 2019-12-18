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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_LEN ; 
 char* GET_REG_NOTE_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ REG_NOTES (scalar_t__) ; 
 int /*<<< orphan*/  REG_NOTE_KIND (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_insn (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  print_value (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

void
dump_insn_slim (FILE *f, rtx x)
{
  char t[BUF_LEN + 32];
  rtx note;

  print_insn (t, x, 1);
  fputs (t, f);
  putc ('\n', f);
  if (INSN_P (x) && REG_NOTES (x))
    for (note = REG_NOTES (x); note; note = XEXP (note, 1))
      {
        print_value (t, XEXP (note, 0), 1);
	fprintf (f, "      %s: %s\n",
		 GET_REG_NOTE_NAME (REG_NOTE_KIND (note)), t);
      }
}