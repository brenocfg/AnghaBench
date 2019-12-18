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
 scalar_t__ ISSPACE (char) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
quoteput (char *s, FILE *f, int needs_quotes)
{
  char *cp;

  for (cp = s; *cp; cp++)
    if (*cp == '\''
	|| *cp == '"'
	|| *cp == '\\'
	|| ISSPACE (*cp)
	|| *cp == ','
	|| *cp == ';')
      needs_quotes = 1;

  if (needs_quotes)
    {
      putc ('"', f);

      while (*s)
	{
	  if (*s == '"' || *s == '\\')
	    putc ('\\', f);

	  putc (*s, f);
	  s++;
	}

      putc ('"', f);
    }
  else
    fputs (s, f);
}