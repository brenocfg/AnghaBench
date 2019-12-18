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
 int /*<<< orphan*/  CTRLC ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int getkey () ; 
 scalar_t__ kbhit () ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/  putchar_e7000 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar_unfiltered (int) ; 
 int quit_flag ; 
 int readchar (int) ; 

__attribute__((used)) static int
expect_n (char **strings)
{
  char *(ptr[10]);
  int n;
  int c;
  char saveaway[100];
  char *buffer = saveaway;
  /* Count number of expect strings  */

  for (n = 0; strings[n]; n++)
    {
      ptr[n] = strings[n];
    }

  while (1)
    {
      int i;
      int gotone = 0;

      c = readchar (1);
      if (c == -1)
	{
	  printf_unfiltered ("[waiting for e7000...]\n");
	}
#ifdef __GO32__
      if (kbhit ())
	{
	  int k = getkey ();

	  if (k == 1)
	    quit_flag = 1;
	}
#endif
      if (quit_flag)
	{
	  putchar_e7000 (CTRLC);	/* interrupt the running program */
	  quit_flag = 0;
	}

      for (i = 0; i < n; i++)
	{
	  if (c == ptr[i][0])
	    {
	      ptr[i]++;
	      if (ptr[i][0] == 0)
		{
		  /* Gone all the way */
		  return i;
		}
	      gotone = 1;
	    }
	  else
	    {
	      ptr[i] = strings[i];
	    }
	}

      if (gotone)
	{
	  /* Save it up incase we find that there was no match */
	  *buffer++ = c;
	}
      else
	{
	  if (buffer != saveaway)
	    {
	      *buffer++ = 0;
	      printf_unfiltered ("%s", buffer);
	      buffer = saveaway;
	    }
	  if (c != -1)
	    {
	      putchar_unfiltered (c);
	      gdb_flush (gdb_stdout);
	    }
	}
    }
}