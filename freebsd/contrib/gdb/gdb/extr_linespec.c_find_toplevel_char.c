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

__attribute__((used)) static char *
find_toplevel_char (char *s, char c)
{
  int quoted = 0;		/* zero if we're not in quotes;
				   '"' if we're in a double-quoted string;
				   '\'' if we're in a single-quoted string.  */
  int depth = 0;		/* Number of unclosed parens we've seen.  */
  char *scan;

  for (scan = s; *scan; scan++)
    {
      if (quoted)
	{
	  if (*scan == quoted)
	    quoted = 0;
	  else if (*scan == '\\' && *(scan + 1))
	    scan++;
	}
      else if (*scan == c && ! quoted && depth == 0)
	return scan;
      else if (*scan == '"' || *scan == '\'')
	quoted = *scan;
      else if (*scan == '(' || *scan == '<')
	depth++;
      else if ((*scan == ')' || *scan == '>') && depth > 0)
	depth--;
    }

  return 0;
}