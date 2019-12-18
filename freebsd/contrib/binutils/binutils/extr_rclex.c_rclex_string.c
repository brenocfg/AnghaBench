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
 char rclex_peekch () ; 
 char rclex_readch () ; 

__attribute__((used)) static void
rclex_string (void)
{
  int c;
  
  while ((c = rclex_peekch ()) != -1)
    {
      if (c == '\n')
	break;
      if (c == '\\')
        {
	  rclex_readch ();
	  if ((c = rclex_peekch ()) == -1 || c == '\n')
	    break;
	  rclex_readch ();
        }
      else if (rclex_readch () == '"')
	{
	  if (rclex_peekch () == '"')
	    rclex_readch ();
	  else
	    break;
	}
    }
}