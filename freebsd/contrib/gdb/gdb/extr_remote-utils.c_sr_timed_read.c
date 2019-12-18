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
 char sr_readchar () ; 

int
sr_timed_read (char *buf, int n)
{
  int i;
  char c;

  i = 0;
  while (i < n)
    {
      c = sr_readchar ();

      if (c == 0)
	return i;
      buf[i] = c;
      i++;

    }
  return i;
}