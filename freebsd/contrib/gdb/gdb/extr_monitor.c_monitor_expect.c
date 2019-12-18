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
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  immediate_quit ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 scalar_t__ monitor_debug_p ; 
 int /*<<< orphan*/  monitor_printable_string (char*,char*,int /*<<< orphan*/ ) ; 
 int readchar (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  timeout ; 

int
monitor_expect (char *string, char *buf, int buflen)
{
  char *p = string;
  int obuflen = buflen;
  int c;

  if (monitor_debug_p)
    {
      char *safe_string = (char *) alloca ((strlen (string) * 4) + 1);
      monitor_printable_string (safe_string, string, 0);
      fprintf_unfiltered (gdb_stdlog, "MON Expecting '%s'\n", safe_string);
    }

  immediate_quit++;
  while (1)
    {
      if (buf)
	{
	  if (buflen < 2)
	    {
	      *buf = '\000';
	      immediate_quit--;
	      return -1;
	    }

	  c = readchar (timeout);
	  if (c == '\000')
	    continue;
	  *buf++ = c;
	  buflen--;
	}
      else
	c = readchar (timeout);

      /* Don't expect any ^C sent to be echoed */

      if (*p == '\003' || c == *p)
	{
	  p++;
	  if (*p == '\0')
	    {
	      immediate_quit--;

	      if (buf)
		{
		  *buf++ = '\000';
		  return obuflen - buflen;
		}
	      else
		return 0;
	    }
	}
      else
	{
	  /* We got a character that doesn't match the string.  We need to
	     back up p, but how far?  If we're looking for "..howdy" and the
	     monitor sends "...howdy"?  There's certainly a match in there,
	     but when we receive the third ".", we won't find it if we just
	     restart the matching at the beginning of the string.

	     This is a Boyer-Moore kind of situation.  We want to reset P to
	     the end of the longest prefix of STRING that is a suffix of
	     what we've read so far.  In the example above, that would be
	     ".." --- the longest prefix of "..howdy" that is a suffix of
	     "...".  This longest prefix could be the empty string, if C
	     is nowhere to be found in STRING.

	     If this longest prefix is not the empty string, it must contain
	     C, so let's search from the end of STRING for instances of C,
	     and see if the portion of STRING before that is a suffix of
	     what we read before C.  Actually, we can search backwards from
	     p, since we know no prefix can be longer than that.

	     Note that we can use STRING itself, along with C, as a record
	     of what we've received so far.  :) */
	  int i;

	  for (i = (p - string) - 1; i >= 0; i--)
	    if (string[i] == c)
	      {
		/* Is this prefix a suffix of what we've read so far?
		   In other words, does
                     string[0 .. i-1] == string[p - i, p - 1]? */
		if (! memcmp (string, p - i, i))
		  {
		    p = string + i + 1;
		    break;
		  }
	      }
	  if (i < 0)
	    p = string;
	}
    }
}