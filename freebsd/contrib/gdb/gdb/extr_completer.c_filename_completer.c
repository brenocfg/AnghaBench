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
 char* rl_completer_word_break_characters ; 
 char* rl_filename_completion_function (char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (int) ; 
 scalar_t__ xrealloc (char**,int) ; 

char **
filename_completer (char *text, char *word)
{
  int subsequent_name;
  char **return_val;
  int return_val_used;
  int return_val_alloced;

  return_val_used = 0;
  /* Small for testing.  */
  return_val_alloced = 1;
  return_val = (char **) xmalloc (return_val_alloced * sizeof (char *));

  subsequent_name = 0;
  while (1)
    {
      char *p;
      p = rl_filename_completion_function (text, subsequent_name);
      if (return_val_used >= return_val_alloced)
	{
	  return_val_alloced *= 2;
	  return_val =
	    (char **) xrealloc (return_val,
				return_val_alloced * sizeof (char *));
	}
      if (p == NULL)
	{
	  return_val[return_val_used++] = p;
	  break;
	}
      /* We need to set subsequent_name to a non-zero value before the
	 continue line below, because otherwise, if the first file seen
	 by GDB is a backup file whose name ends in a `~', we will loop
	 indefinitely.  */
      subsequent_name = 1;
      /* Like emacs, don't complete on old versions.  Especially useful
         in the "source" command.  */
      if (p[strlen (p) - 1] == '~')
	continue;

      {
	char *q;
	if (word == text)
	  /* Return exactly p.  */
	  return_val[return_val_used++] = p;
	else if (word > text)
	  {
	    /* Return some portion of p.  */
	    q = xmalloc (strlen (p) + 5);
	    strcpy (q, p + (word - text));
	    return_val[return_val_used++] = q;
	    xfree (p);
	  }
	else
	  {
	    /* Return some of TEXT plus p.  */
	    q = xmalloc (strlen (p) + (text - word) + 5);
	    strncpy (q, word, text - word);
	    q[text - word] = '\0';
	    strcat (q, p);
	    return_val[return_val_used++] = q;
	    xfree (p);
	  }
      }
    }
#if 0
  /* There is no way to do this just long enough to affect quote inserting
     without also affecting the next completion.  This should be fixed in
     readline.  FIXME.  */
  /* Insure that readline does the right thing
     with respect to inserting quotes.  */
  rl_completer_word_break_characters = "";
#endif
  return return_val;
}