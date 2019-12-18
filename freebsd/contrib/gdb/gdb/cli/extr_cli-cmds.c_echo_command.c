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

/* Variables and functions */
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int parse_escape (char**) ; 
 int /*<<< orphan*/  printf_filtered (char*,int) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
echo_command (char *text, int from_tty)
{
  char *p = text;
  int c;

  if (text)
    while ((c = *p++) != '\0')
      {
	if (c == '\\')
	  {
	    /* \ at end of argument is used after spaces
	       so they won't be lost.  */
	    if (*p == 0)
	      return;

	    c = parse_escape (&p);
	    if (c >= 0)
	      printf_filtered ("%c", c);
	  }
	else
	  printf_filtered ("%c", c);
      }

  /* Force this output to appear now.  */
  wrap_here ("");
  gdb_flush (gdb_stdout);
}