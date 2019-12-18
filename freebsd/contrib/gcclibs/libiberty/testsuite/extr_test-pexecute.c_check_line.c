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
 int EOF ; 
 int /*<<< orphan*/  fatal_error (int,char*,int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const,...) ; 

__attribute__((used)) static void
check_line (int line, FILE *e, const char *str)
{
  const char *p;
  int c;
  char buf[1000];

  p = str;
  while (1)
    {
      c = getc (e);

      if (*p == '\0')
	{
	  if (c != '\n')
	    {
	      snprintf (buf, sizeof buf, "got '%c' when expecting newline", c);
	      fatal_error (line, buf, 0);
	    }
	  c = getc (e);
	  if (c != EOF)
	    {
	      snprintf (buf, sizeof buf, "got '%c' when expecting EOF", c);
	      fatal_error (line, buf, 0);
	    }
	  return;
	}

      if (c != *p)
	{
	  snprintf (buf, sizeof buf, "expected '%c', got '%c'", *p, c);
	  fatal_error (line, buf, 0);
	}

      ++p;
    }
}