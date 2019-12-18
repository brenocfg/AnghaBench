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
 int /*<<< orphan*/  immediate_quit ; 
 char sr_readchar () ; 

void
sr_expect (char *string)
{
  char *p = string;

  immediate_quit++;
  while (1)
    {
      if (sr_readchar () == *p)
	{
	  p++;
	  if (*p == '\0')
	    {
	      immediate_quit--;
	      return;
	    }
	}
      else
	p = string;
    }
}