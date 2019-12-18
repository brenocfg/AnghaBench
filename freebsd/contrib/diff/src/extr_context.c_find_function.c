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
typedef  scalar_t__ lin ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 size_t LIN_MAX ; 
 int MIN (size_t,int /*<<< orphan*/ ) ; 
 size_t find_function_last_match ; 
 scalar_t__ find_function_last_search ; 
 int /*<<< orphan*/  function_regexp ; 
 scalar_t__ re_search (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char const *
find_function (char const * const *linbuf, lin linenum)
{
  lin i = linenum;
  lin last = find_function_last_search;
  find_function_last_search = i;

  while (last <= --i)
    {
      /* See if this line is what we want.  */
      char const *line = linbuf[i];
      size_t linelen = linbuf[i + 1] - line - 1;

      /* FIXME: re_search's size args should be size_t, not int.  */
      int len = MIN (linelen, INT_MAX);

      if (0 <= re_search (&function_regexp, line, len, 0, len, 0))
	{
	  find_function_last_match = i;
	  return line;
	}
    }
  /* If we search back to where we started searching the previous time,
     find the line we found last time.  */
  if (find_function_last_match != LIN_MAX)
    return linbuf[find_function_last_match];

  return 0;
}