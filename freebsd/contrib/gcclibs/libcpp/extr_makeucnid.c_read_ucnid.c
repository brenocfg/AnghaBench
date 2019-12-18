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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int C99 ; 
 unsigned int CXX ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 unsigned int* flags ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ isxdigit (char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 unsigned long strtoul (char*,char**,int) ; 

__attribute__((used)) static void
read_ucnid (const char *fname)
{
  FILE *f = fopen (fname, "r");
  unsigned fl = 0;
  
  if (!f)
    fail ("opening ucnid.tab");
  for (;;)
    {
      char line[256];

      if (!fgets (line, sizeof (line), f))
	break;
      if (strcmp (line, "[C99]\n") == 0)
	fl = C99;
      else if (strcmp (line, "[CXX]\n") == 0)
	fl = CXX;
      else if (isxdigit (line[0]))
	{
	  char *l = line;
	  while (*l)
	    {
	      unsigned long start, end;
	      char *endptr;
	      start = strtoul (l, &endptr, 16);
	      if (endptr == l || (*endptr != '-' && ! isspace (*endptr)))
		fail ("parsing ucnid.tab [1]");
	      l = endptr;
	      if (*l != '-')
		end = start;
	      else
		{
		  end = strtoul (l + 1, &endptr, 16);
		  if (end < start)
		    fail ("parsing ucnid.tab, end before start");
		  l = endptr;
		  if (! isspace (*l))
		    fail ("parsing ucnid.tab, junk after range");
		}
	      while (isspace (*l))
		l++;
	      if (end > 0xFFFF)
		fail ("parsing ucnid.tab, end too large");
	      while (start <= end)
		flags[start++] |= fl;
	    }
	}
    }
  if (ferror (f))
    fail ("reading ucnid.tab");
  fclose (f);
}