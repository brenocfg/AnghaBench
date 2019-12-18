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
 int rclex_lastch ; 
 int rclex_readch () ; 
 scalar_t__* rclex_tok ; 
 size_t rclex_tok_pos ; 

__attribute__((used)) static int
rclex_peekch (void)
{
  int r;

  if ((r = rclex_lastch) == -1)
    {
      if ((r = rclex_readch ()) != -1)
	{
	  rclex_lastch = r;
	  if (rclex_tok_pos > 0)
	    rclex_tok[--rclex_tok_pos] = 0;
	}
    }
  return r;
}