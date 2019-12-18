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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 

const char *
spaces (int count)
{
  register char *t;
  static char *buf;
  static int maxsize;

  if (count > maxsize)
    {
      if (buf)
	{
	  free (buf);
	}
      buf = (char *) malloc (count + 1);
      if (buf == (char *) 0)
	return 0;
      for (t = buf + count ; t != buf ; )
	{
	  *--t = ' ';
	}
      maxsize = count;
      buf[count] = '\0';
    }
  return (const char *) (buf + maxsize - count);
}