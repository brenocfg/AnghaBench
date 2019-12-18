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
 char* xmalloc (size_t) ; 

__attribute__((used)) static char *
argv_to_cmdline (char *const *argv)
{
  char *cmdline;
  char *p;
  size_t cmdline_len;
  int i, j, k;

  cmdline_len = 0;
  for (i = 0; argv[i]; i++)
    {
      /* We quote every last argument.  This simplifies the problem;
	 we need only escape embedded double-quotes and immediately
	 preceeding backslash characters.  A sequence of backslach characters
	 that is not follwed by a double quote character will not be
	 escaped.  */
      for (j = 0; argv[i][j]; j++)
	{
	  if (argv[i][j] == '"')
	    {
	      /* Escape preceeding backslashes.  */
	      for (k = j - 1; k >= 0 && argv[i][k] == '\\'; k--)
		cmdline_len++;
	      /* Escape the qote character.  */
	      cmdline_len++;
	    }
	}
      /* Trailing backslashes also need to be escaped because they will be
         followed by the terminating quote.  */
      for (k = j - 1; k >= 0 && argv[i][k] == '\\'; k--)
	cmdline_len++;
      cmdline_len += j;
      cmdline_len += 3;  /* for leading and trailing quotes and space */
    }
  cmdline = xmalloc (cmdline_len);
  p = cmdline;
  for (i = 0; argv[i]; i++)
    {
      *p++ = '"';
      for (j = 0; argv[i][j]; j++)
	{
	  if (argv[i][j] == '"')
	    {
	      for (k = j - 1; k >= 0 && argv[i][k] == '\\'; k--)
		*p++ = '\\';
	      *p++ = '\\';
	    }
	  *p++ = argv[i][j];
	}
      for (k = j - 1; k >= 0 && argv[i][k] == '\\'; k--)
	*p++ = '\\';
      *p++ = '"';
      *p++ = ' ';
    }
  p[-1] = '\0';
  return cmdline;
}