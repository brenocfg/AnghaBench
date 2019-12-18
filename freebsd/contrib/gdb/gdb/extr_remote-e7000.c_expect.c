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
 scalar_t__ echo ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ normal (char) ; 
 int /*<<< orphan*/  putchar_unfiltered (int) ; 
 int readchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static void
expect (char *string)
{
  char *p = string;
  int c;
  int nl = 0;

  while (1)
    {
      c = readchar (timeout);

      if (echo)
	{
	  if (c == '\r' || c == '\n')
	    {
	      if (!nl)
		putchar_unfiltered ('\n');
	      nl = 1;
	    }
	  else
	    {
	      nl = 0;
	      putchar_unfiltered (c);
	    }
	  gdb_flush (gdb_stdout);
	}
      if (normal (c) == normal (*p++))
	{
	  if (*p == '\0')
	    return;
	}
      else
	{
	  p = string;

	  if (normal (c) == normal (string[0]))
	    p++;
	}
    }
}