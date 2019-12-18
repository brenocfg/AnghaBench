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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  source_lineno ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

int
skip_spaces (FILE *fp, int c)
{
  for (;;)
    {
      if (c == ' ' || c == '\t')
	c = getc (fp);
      else if (c == '/')
	{
	  c = getc (fp);
	  if (c != '*')
	    {
	      ungetc (c, fp);
	      return '/';
	    }
	  c = getc (fp);
	  for (;;)
	    {
	      if (c == EOF)
		return EOF;
	      else if (c != '*')
		{
		  if (c == '\n')
		    source_lineno++, lineno++;
		  c = getc (fp);
		}
	      else if ((c = getc (fp)) == '/')
		return getc (fp);
	    }
	}
      else
	break;
    }
  return c;
}