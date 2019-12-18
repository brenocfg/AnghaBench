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
 int /*<<< orphan*/  QUIT ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  fputc_unfiltered (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int sr_readchar () ; 
 int strlen (char*) ; 

int
gr_multi_scan (char *list[], int passthrough)
{
  char *swallowed = NULL;	/* holding area */
  char *swallowed_p = swallowed;	/* Current position in swallowed.  */
  int ch;
  int ch_handled;
  int i;
  int string_count;
  int max_length;
  char **plist;

  /* Look through the strings.  Count them.  Find the largest one so we can
     allocate a holding area.  */

  for (max_length = string_count = i = 0;
       list[i] != NULL;
       ++i, ++string_count)
    {
      int length = strlen (list[i]);

      if (length > max_length)
	max_length = length;
    }

  /* if we have no strings, then something is wrong. */
  if (string_count == 0)
    return (-1);

  /* otherwise, we will need a holding area big enough to hold almost two
     copies of our largest string.  */
  swallowed_p = swallowed = alloca (max_length << 1);

  /* and a list of pointers to current scan points. */
  plist = (char **) alloca (string_count * sizeof (*plist));

  /* and initialize */
  for (i = 0; i < string_count; ++i)
    plist[i] = list[i];

  for (ch = sr_readchar (); /* loop forever */ ; ch = sr_readchar ())
    {
      QUIT;			/* Let user quit and leave process running */
      ch_handled = 0;

      for (i = 0; i < string_count; ++i)
	{
	  if (ch == *plist[i] || *plist[i] == '?')
	    {
	      ++plist[i];
	      if (*plist[i] == '\0')
		return (i);

	      if (!ch_handled)
		*swallowed_p++ = ch;

	      ch_handled = 1;
	    }
	  else
	    plist[i] = list[i];
	}

      if (!ch_handled)
	{
	  char *p;

	  /* Print out any characters which have been swallowed.  */
	  if (passthrough)
	    {
	      for (p = swallowed; p < swallowed_p; ++p)
		fputc_unfiltered (*p, gdb_stdout);

	      fputc_unfiltered (ch, gdb_stdout);
	    }

	  swallowed_p = swallowed;
	}
    }
#if 0
  /* Never reached.  */
  return (-1);
#endif
}