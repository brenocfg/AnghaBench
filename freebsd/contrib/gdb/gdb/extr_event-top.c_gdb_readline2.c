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
typedef  int /*<<< orphan*/  gdb_client_data ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  ISATTY (scalar_t__) ; 
 int fgetc (scalar_t__) ; 
 int /*<<< orphan*/  input_handler (char*) ; 
 scalar_t__ instream ; 
 int /*<<< orphan*/  setbuf (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stdin ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int /*<<< orphan*/  stub2 (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (char*,int) ; 

void
gdb_readline2 (gdb_client_data client_data)
{
  int c;
  char *result;
  int input_index = 0;
  int result_size = 80;
  static int done_once = 0;

  /* Unbuffer the input stream, so that, later on, the calls to fgetc
     fetch only one char at the time from the stream. The fgetc's will
     get up to the first newline, but there may be more chars in the
     stream after '\n'. If we buffer the input and fgetc drains the
     stream, getting stuff beyond the newline as well, a select, done
     afterwards will not trigger. */
  if (!done_once && !ISATTY (instream))
    {
      setbuf (instream, NULL);
      done_once = 1;
    }

  result = (char *) xmalloc (result_size);

  /* We still need the while loop here, even though it would seem
     obvious to invoke gdb_readline2 at every character entered.  If
     not using the readline library, the terminal is in cooked mode,
     which sends the characters all at once. Poll will notice that the
     input fd has changed state only after enter is pressed. At this
     point we still need to fetch all the chars entered. */

  while (1)
    {
      /* Read from stdin if we are executing a user defined command.
         This is the right thing for prompt_for_continue, at least.  */
      c = fgetc (instream ? instream : stdin);

      if (c == EOF)
	{
	  if (input_index > 0)
	    /* The last line does not end with a newline.  Return it, and
	       if we are called again fgetc will still return EOF and
	       we'll return NULL then.  */
	    break;
	  xfree (result);
	  (*input_handler) (0);
	}

      if (c == '\n')
#ifndef CRLF_SOURCE_FILES
	break;
#else
	{
	  if (input_index > 0 && result[input_index - 1] == '\r')
	    input_index--;
	  break;
	}
#endif

      result[input_index++] = c;
      while (input_index >= result_size)
	{
	  result_size *= 2;
	  result = (char *) xrealloc (result, result_size);
	}
    }

  result[input_index++] = '\0';
  (*input_handler) (result);
}