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
 int EOF ; 
 int INF_GET () ; 
 int /*<<< orphan*/  INF_UNGET (int) ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  source_lineno ; 

__attribute__((used)) static int
inf_skip_spaces (int c)
{
  for (;;)
    {
      if (c == ' ' || c == '\t')
	c = INF_GET ();
      else if (c == '/')
	{
	  c = INF_GET ();
	  if (c != '*')
	    {
	      (void) INF_UNGET (c);
	      return '/';
	    }
	  c = INF_GET ();
	  for (;;)
	    {
	      if (c == EOF)
		return EOF;
	      else if (c != '*')
		{
		  if (c == '\n')
		    source_lineno++, lineno++;
		  c = INF_GET ();
		}
	      else if ((c = INF_GET ()) == '/')
		return INF_GET ();
	    }
	}
      else
	break;
    }
  return c;
}