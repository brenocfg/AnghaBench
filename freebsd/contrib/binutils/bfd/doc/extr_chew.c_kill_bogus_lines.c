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
typedef  int /*<<< orphan*/  string_type ;

/* Variables and functions */
 char at (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  catchar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  delete_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_string (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  pc ; 
 int /*<<< orphan*/ * tos ; 

__attribute__((used)) static void
kill_bogus_lines ()
{
  int sl;

  int idx = 0;
  int c;
  int dot = 0;

  string_type out;
  init_string (&out);
  /* Drop leading nl.  */
  while (at (tos, idx) == '\n')
    {
      idx++;
    }
  c = idx;

  /* If the first char is a '.' prepend a newline so that it is
     recognized properly later.  */
  if (at (tos, idx) == '.')
    catchar (&out, '\n');

  /* Find the last char.  */
  while (at (tos, idx))
    {
      idx++;
    }

  /* Find the last non white before the nl.  */
  idx--;

  while (idx && isspace ((unsigned char) at (tos, idx)))
    idx--;
  idx++;

  /* Copy buffer upto last char, but blank lines before and after
     dots don't count.  */
  sl = 1;

  while (c < idx)
    {
      if (at (tos, c) == '\n'
	  && at (tos, c + 1) == '\n'
	  && at (tos, c + 2) == '.')
	{
	  /* Ignore two newlines before a dot.  */
	  c++;
	}
      else if (at (tos, c) == '.' && sl)
	{
	  /* remember that this line started with a dot.  */
	  dot = 2;
	}
      else if (at (tos, c) == '\n'
	       && at (tos, c + 1) == '\n'
	       && dot)
	{
	  c++;
	  /* Ignore two newlines when last line was dot.  */
	}

      catchar (&out, at (tos, c));
      if (at (tos, c) == '\n')
	{
	  sl = 1;

	  if (dot == 2)
	    dot = 1;
	  else
	    dot = 0;
	}
      else
	sl = 0;

      c++;

    }

  /* Append nl.  */
  catchar (&out, '\n');
  pc++;
  delete_string (tos);
  *tos = out;

}