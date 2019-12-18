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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
quote_string_for_make (FILE *file, char *src)
{
  char *p = src;
  int i = 0;

  for (;;)
    {
      char c = *p++;

      switch (c)
	{
	case '\0':
	case ' ':
	case '\t':
	  {
	    /* GNU make uses a weird quoting scheme for white space.
	       A space or tab preceded by 2N+1 backslashes represents
	       N backslashes followed by space; a space or tab
	       preceded by 2N backslashes represents N backslashes at
	       the end of a file name; and backslashes in other
	       contexts should not be doubled.  */
	    char *q;

	    for (q = p - 1; src < q && q[-1] == '\\'; q--)
	      {
		if (file)
		  putc ('\\', file);
		i++;
	      }
	  }
	  if (!c)
	    return i;
	  if (file)
	    putc ('\\', file);
	  i++;
	  goto ordinary_char;

	case '$':
	  if (file)
	    putc (c, file);
	  i++;
	  /* Fall through.  This can mishandle things like "$(" but
	     there's no easy fix.  */
	default:
	ordinary_char:
	  /* This can mishandle characters in the string "\0\n%*?[\\~";
	     exactly which chars are mishandled depends on the `make' version.
	     We know of no portable solution for this;
	     even GNU make 3.76.1 doesn't solve the problem entirely.
	     (Also, '\0' is mishandled due to our calling conventions.)  */
	  if (file)
	    putc (c, file);
	  i++;
	  break;
	}
    }
}